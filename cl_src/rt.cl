#ifndef EPSILON
# define EPSILON 0.00001f
#endif

#define filterWidth 9
#define filterHeight 9

#if __OPENCL_VERSION__ < 120
# define COS cosf
#else
# define COS cos
#endif

typedef enum		e_type
{
	plan,
	triangle,
	sphere,
	cylindre,
	cone,
	para,
	light,
	start_obj,
	end_obj,
	end
}					t_type;

typedef struct 		s_obj
{
	float4			pos;
	float4			dir;
	float			tet;
	float			phi;
	float			rot;
	float4			min;
	float4			max;
	int				col;
	float			diff;
	float			refl;
	float			trans;
	float			refr;
	t_type			type;
	float			r;
	float			su;
	float			sd;
	float			alpha;
	char			caps;
	float4			p1;
	float4			p2;
	float4			p3;
}					t_obj;

typedef struct		s_cam
{
	float4			ori;
	float4			dirx;
	float4			diry;
	float4			dirz;
	int2			size;
	float2			viewplane;
	float4			p;
}					t_cam;

typedef struct		s_ray
{
	float4			ori;
	float4			dir;
	float			t;
	int				imp;
}					t_ray;

float4			qt_conjugate(float4 qt)
{
	float4	ret;

	ret = -qt;
	ret.w = qt.w;
	return (ret);
}

float4			qt_cross(float4 u, float4 v)
{
	float4	ret;

	ret.x = (u.w * v.x) + (u.x * v.w) + (u.y * v.z) - (u.z * v.y);
	ret.y = (u.w * v.y) - (u.x * v.z) + (u.y * v.w) + (u.z * v.x);
	ret.z = (u.w * v.z) + (u.x * v.y) - (u.y * v.x) + (u.z * v.w);
	ret.w = (u.w * v.w) - (u.x * v.x) - (u.y * v.y) - (u.z * v.z);
	return (ret); 
}

float4			qt_gen(float4 axis, float tet)
{
	float4	ret;

	ret = axis * sin(tet / 2);
	ret.w = cos(tet / 2);
	return (ret);
}

float4			qt_rot(float4 qt, float4 p)
{
	float4	ret;

	ret = qt_cross(qt, p);
	ret = qt_cross(ret, qt_conjugate(qt));
	return (ret);
}

float			sq(float a)
{
	return (a * a);
}

/*
** equations
*/

t_ray			rot_ray(t_ray from, float tet, float phi, float4 center)
{
	float4	qt;
	float4	tmp;
	float4	yaxis = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	float4	zaxis = (float4)(0.0f, 0.0f, 1.0f, 0.0f);
	t_ray	ret;

	qt = qt_cross(qt_gen(zaxis, tet), qt_gen(yaxis, phi));
	// qt = qt_cross(qt, qt_gen(o[i].dir, o[i].rot));
	ret.dir = qt_rot(qt, from.dir);
	tmp = center - from.ori;
	tmp = qt_rot(qt, tmp);
	ret.ori = center - tmp;
	return (ret);
}

int				quadratic(float a, float b, float c, float2 *ret)
{
	float	delta;

	delta = b * b - (4.0f * a * c);
	if (delta <= 0)
		return (0);
	ret->x = (b - sqrt(delta)) / (2.0f * a);
	ret->y = (b + sqrt(delta)) / (2.0f * a);
	return (1);
}

int				rt_plan(__global t_obj *o, t_ray *ray)
{
	float	d = dot(o->dir, ray->dir);
	float	t;

	// ray paralele au plan
	if (d > -0.01f && d < 0.01f)
		return (0);
	t = dot(o->pos + EPSILON - ray->ori, o->dir) / d;
	if (t > EPSILON && (t < ray->t || ray->t < EPSILON))
	{
		ray->t = t;
		return (d > 0 ? -1 : 1);
	}
	return (0);
}

float4		norm_sphere(__global t_obj *o, float4 hit, int id)
{
	return(hit - o[id].pos);
}

float4		norm_cone(__global t_obj *o, float4 hit, int id, t_ray ray)
{
	float4	ret;
	float4	dir;
	float	k;
	float	m;

	dir = normalize(o[id].dir);
	k = tan(o[id].alpha * M_PI / 360.0f);
	m = dot(normalize(ray.dir), dir) * ray.t + dot(ray.ori - o[id].pos, dir);
	ret = normalize(hit - o[id].pos - dir - (1.0f + k * k) * dir * m);
	return(ret);
}

float4		norm_cylindre(__global t_obj *o, float4 hit, int id)
{
	float4	ret;
	float4	vec;
	float	k;

	vec = o[id].pos;
	vec.y = hit.y;
	ret = hit - vec;
	return(ret);
}

/*
   float4			get_normale(float4 hit, __global t_obj *o,int id)
   {
   switch (o[id].type) {
   case sphere :
   return(norm_sphere(o, hit, id));
   break;
   case plan :
   return(norm_plan(o, hit, id));
   break;
   case triangle :
   return(norm_tri(o, hit, id));
   break;
   case cylindre :
   return(norm_cyl(o, hit, id));
   break;
   case cone :
   return(norm_cone(o, hit, id));
   break;
   }
   }
   */


float4			refl(float4 ray, float4 normale)
{
	float4		ret;
	float4		dir;
	float4		norma;
	float		dp;

	dir = normalize(ray);
	norma = normalize(normale);
	dp = 2 * dot(dir, norma);
	ret = norma * dp;
	ret = dir - ret;
	return(ret);
}



int				get_light(__global t_obj *o, __global t_obj *l, float4 hit)
{
	t_ray	ray;
	int		nb;
	int		i;
	int		id;
	int		color;
	float4	col;

	nb = 0;
	color = 0;
	i = -1;

	while(l[nb].type != end)
		nb++;
	col = 0;
	while(l[++i].type != end)
	{
		ray.ori = hit;
		ray.dir = ray.ori - l[i].pos;
		ray.dir = normalize(ray.dir);
		if((id = ray_match(o, &ray)) == -1)
		{
			col.x += (l[i].col & 0xFF0000) / 0x10000;
			col.y += (l[i].col & 0xFF00) / 0x100;
			col.z += (l[i].col & 0xFF);
		}
	}
	if(nb);  
	col /= nb;
	color += (((int)col.x) &  0xFF0000) / 0x10000;
	color += (((int)col.y) & 0xFF00) / 0x100;
	color += (((int)col.z) & 0xFF);
	return(color);
}

int				diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in, __global int *tex)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char i;
	unsigned char j;
	unsigned char k;
	float4 hit;
	float4 normale;
	float4 vlight;
	float4 fla;
	float4 mid;
	float4 tmp;
	float4	coef;
	float4	ctsn;
	float2	polar;
	float norme;
	float dp;
	float spec;
	float rl;
	float gl;
	float bl;
	int lol;
	int color;
	t_ray shad;

	color = o[id].col;
	hit = ray.dir * *t + ray.ori;
	coef.x = 4.0;
	coef.y = 1.0;
	coef.z = 4.0;
	ctsn.x = hit.x - o[id].pos.x;
	ctsn.y = hit.y - o[id].pos.y;
	ctsn.z = hit.z - o[id].pos.z;
	if(o[id].type == sphere)
	{
		normale = norm_sphere(o, hit, id);
		polar.x = (atan(ctsn.y / sqrt(-ctsn.z * -ctsn.z + ctsn.x * ctsn.x)));
		polar.y = (atan(ctsn.x / -ctsn.z));
//		if ((int)((polar.x + M_PI) * 5) % 2)
//			color = 0xFFFFFF - color;
//		if ((int)((polar.y + M_PI) * 5) % 2)
//			color = 0xFFFFFF - color;
//		normale.x += sin((polar.y + polar.x) * 20.0) * 1.5;
//		normale.y += sin((polar.y + polar.x) * 20.0) * 1.5;
//		normale.z += sin((polar.y + polar.x) * 20.0) * 1.5;
//		if(polar.x < M_PI_2_F && polar.y < EPSILON)
//			color = tex[1];
//		else if(polar.x < M_PI_2_F && polar.y > EPSILON)
//			color = tex[2];
//		if(polar.x < EPSILON)
//			color = tex[3];
//		polar.y /= 2;
//		if(polar.y > EPSILON && polar.x > EPSILON)
//			color = tex[1];
//		if(polar.y > EPSILON && polar.x < EPSILON)
//			color = tex[2];
//		if(polar.y < EPSILON && polar.x < EPSILON)
//			color = tex[3];
//		if(polar.y < EPSILON && polar.x > EPSILON)
//			color = tex[4];
//		else if(polar.x > M_PI_2_F && polar.y > EPSILON)
//			color = tex[4];
	}
	else if (o[id].type == plan)
	{
		normale = o[id].dir;
		if ((int)(ctsn.x / 5.0 + (ctsn.x > 0 ? 1.0 : 0.0)) % 2)
			color = 0xFFFFFF - color;
		if ((int)(ctsn.z / 5.0 + (ctsn.z > 0 ? 1.0 : 0.0)) % 2)
			color = 0xFFFFFF - color;
		if (color != 0xFFFFFF - o[id].col)
		{
			hit.x -= sin(ctsn.x);
			hit.y -= sin(ctsn.y);
			hit.z -= sin(ctsn.z);
//			normale.x += sin(ctsn.x * o[id].dir.x * 10.0) * 1.2;
//			normale.y += sin(ctsn.y * o[id].dir.y * 10.0) * 1.2;
//			normale.z += sin(ctsn.z * o[id].dir.z * 10.0) * 1.2;
		}
		else
		{
//			normale.x += cos(ctsn.x * o[id].dir.x * 10.0) * 1.2;
//			normale.y += cos(ctsn.y * o[id].dir.y * 10.0) * 1.2;
//			normale.z += cos(ctsn.z * o[id].dir.z * 10.0) * 1.2;
			color = 0xFFFFFF - color;
		}
	}
	else if (o[id].type == cone)
	{
		normale = norm_cone(o, hit, id, ray);
		polar.x = ctsn.x * o[id].dir.x + ctsn.y * o[id].dir.y + ctsn.z * o[id].dir.z;
		polar.y = (atan(ctsn.x / -ctsn.z));
//		if ((int)(fabs(polar.x) + 0.5) % 2)
//			color = 0xFFFFFF - color;
		if ((int)((polar.y + M_PI) * 5) % 2)
			color = 0xFFFFFF - color;
	}
	else if (o[id].type == cylindre)
	{
		normale = norm_cylindre(o, hit, id);
		polar.x = ctsn.y;
		polar.y = (atan(ctsn.x / -ctsn.z));
//		if ((int)(fabs(polar.x) + 0.5) % 2)
//			color = 0xFFFFFF - color;
//		if ((int)((polar.y + M_PI) * 5) % 2)
//			color = 0xFFFFFF - color;
//		normale.x += sin(polar.y * 40.0) * 1.2;
		normale.y += sin((10.0 * polar.y + polar.x) * 3.0);
//		normale.z += cos(polar.y * 40.0) * 1.2;
	}
	else if (o[id].type == para)
	{
		normale = hit - o[id].pos;
	}
	else
		return(color);
	vlight = l[in].pos - hit;
	shad.ori = hit;
	shad.dir = normalize(vlight);
	tmp = vlight;
	norme = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	r = (color & 0xFF0000) / 0x10000;
	g = (color & 0xFF00) / 0x100;
	b = (color & 0xFF);
	if ((lol = ray_match(o, &shad)) != -1 && shad.t < norme)
	{
		r /= 50;
		g /= 50;
		b /= 50;
		return(r * 0x10000 + g * 0x100 + b);
	}
	dp = dot(normalize(vlight), normalize(normale));
	float4 rp = dot(normalize(refl(ray.dir, normale)), vlight);
	rl = (l[in].col & 0xFF0000) / 0x10000 / 255.0;
	gl = (l[in].col & 0xFF00) / 0x100 / 255.0;
	bl = (l[in].col & 0xFF) / 255.0;
	r = r * dp * (l[in].r / (norme * norme)) * rl > 255 ? 255 : r * dp * (l[in].r / (norme * norme)) * rl + r * 0.05;
	g = g * dp * (l[in].r / (norme * norme)) * gl > 255 ? 255 : g * dp * (l[in].r / (norme * norme)) * gl + g * 0.05;
	b = b * dp * (l[in].r / (norme * norme)) * bl > 255 ? 255 : b * dp * (l[in].r / (norme * norme)) * bl + b * 0.05;
//	ray.dir *= -1;
	mid = (normalize(-ray.dir) + normalize(vlight)) / 2;
	spec = pow(dot(normalize(mid), normalize(normale)) / 1.005, 500);
	spec *= l[in].r / 100;
	fla.x = ((float)((l[in].col & 0xFF0000) / 0x010000)) * spec;
	fla.y = ((float)((l[in].col & 0x00FF00) / 0x000100)) * spec;
	fla.z = ((float)(l[in].col & 0x0000FF) / 0x000001) * spec;
	fla.x = fla.x > 255.0 ? 255.0 : fla.x;
	fla.y = fla.y > 255.0 ? 255.0 : fla.y;
	fla.z = fla.z > 255.0 ? 255.0 : fla.z;
	i = floor(fla.x);
	j = floor(fla.y);
	k = floor(fla.z);
	r = r + i > 255 ? 255 : r + i;
	g = g + j > 255 ? 255 : g + j;
	b = b + k > 255 ? 255 : b + k;
	color = r * 0x10000 + g * 0x100 + b;
	return(color);
}

int				rt_triangle(__global t_obj *o, t_ray *ray)
{
	float4		e1;
	float4		e2;
	float4		p;
	float4		q;
	float4		T;
	float		d;
	float		u;
	float		v;
	float		t;

	e1 = o->p2 - o->p1;
	e2 = o->p3 - o->p1;
	// vecteurs definissant les triangles
	p = cross(ray->dir, e2);
	//normale a la direction et e2
	d = dot(e1, p);
	// derminant se raprochant de 0 quand on est paralelle au triangle et servant a mettre le triangle a echelle 1
	if (d > -EPSILON && d < EPSILON)
		return (0);
	T = ray->ori - o->p1;
	// T est le vecteur entre l'origine et le sommet reunissant les deux vecteurs du triangle
	u = dot(T, p) / d;
	// on regarde si le vecteur est dansle premier vecteur du triangle
	if (u < 0 || u > 1)
		return (0);
	q = cross(T, e1);
	v = dot(ray->dir, q) / d;
	// on regarde si le vecteur est dans le deuxieme vecteur du triangle, si u + v pour ne pas faire un parallelogramme
	if (v < 0 || v + u > 1)
		return (0);
	t = dot(e2, q) / d;
	if (t > 0.01 && (t < ray->t || ray->t <= 0))
	{
		ray->t = t;
		return (d > 0 ? -1 : 1);
	}
	return (0);
}

int				rt_cone(__global t_obj *o, t_ray *ray)
{
	float2	t;
	float	a;
	float	b;
	float	c;
	float	k;
	float4	odir;
	float4	d;
	float4	x;

	d = normalize(ray->dir);
	odir = normalize(o->dir);
	x = ray->ori - o->pos;
	k = tan(o->alpha / 360.0f * M_PI);
	k = 1.0f + k * k;
	a = dot(d, d) - sq(dot(d, odir)) * k;
	b = (dot(d, x) - k * dot(d, odir) * dot(x, odir)) * -2.0f;
	c = dot(x, x) - k * sq(dot(x, odir));
	if ((quadratic(a, b, c, &t)))
	{
		if (t.x < t.y && t.x > 0.01f && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			return (1);
		}
		else if (t.y > 0.01f && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			return (-1);
		}
	}
	return (0);
}

int				rt_cylindre(__global t_obj *o, int i, t_ray *ray, int obj)
{
	float2	t;
	float4	pos;
	t_ray	cpy;
	t_ray	oray;
	float4	ocpy;
	float	a;
	float	b;
	float	c;
	float4	rpos;

	rpos = (obj != -1) ? obj + o[i].pos : o[i].pos;
//	cpy = (obj != -1) ? rot_ray(*ray, o[obj].tet, o[obj].pos) : *ray;
	cpy = *ray;
	ocpy = o->pos;
	ocpy.y = 0;
	cpy.dir.y = 0;
	cpy.ori.y = 0;
	pos = ocpy - cpy.ori;
	a = dot(cpy.dir, cpy.dir);
	b = 2.0f * dot(cpy.dir, pos);
	c = dot(pos, pos) - o[i].r * o[i].r;
	if(quadratic(a, b, c, &t))
	{
		if(t.x < t.y && t.x > 0.01 && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			return(1);
		}
		else if(t.y > 0.01 && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			return(-1);
		}
	}
	return (0);
}

int				rt_sphere(__global t_obj *o, t_ray *ray)
{
	float2	t;
	float4	pos;
	float	a;
	float	b;
	float	c;

	pos = o->pos - ray->ori;
	a = dot(ray->dir, ray->dir);
	b = 2.0f * dot(ray->dir, pos);
	c = dot(pos, pos) - o->r * o->r;
	if ((quadratic(a, b, c, &t)))
	{
		if (t.x < t.y && t.x > 0.001 && (t.x < ray->t || ray->t <= 0.001))
		{
			if (t.x < 0.001)
				ray->t = 0.001;
			else
				ray->t = t.x;
			return (1);
		}
		else if (t.y > 0.001 && (t.y < ray->t || ray->t <= 0.001))
		{
			if (t.y < 0.001)
				ray->t = 0.001;
			else
				ray->t = t.y;
			return (-1);
		}
	}
	return (0);
}

int				rt_para(__global t_obj *o, t_ray *ray)
{
	float2	t;
	float4	pos;
	float	a;
	float	b;
	float	c;
	t_ray	rcp;
	float4	opos;

	rcp = *ray;
	opos = o->pos;
//	opos.y = 0;
//	rcp.dir.y = 0;
//	rcp.ori.y = 0;
	pos = rcp.ori - opos;
	float4	k = dot(pos, o->dir);
	a = dot(rcp.dir, rcp.dir) - pow(dot(rcp.dir, o->dir), 2);
	b = 2.0f * (dot(rcp.dir, pos) - dot(rcp.dir, o->dir));// * (dot(pos, o->dir) + 2 * k));
	c = dot(pos, pos) - dot(pos, o->dir) * (dot(pos, o->dir));// + 4 * k);
	if ((quadratic(a, b, c, &t)))
	{
		if (t.x < t.y && t.x > 0.001 && (t.x < ray->t || ray->t <= 0.001))
		{
//			if (t.x < 0.001)
//				ray->t = 0.001;
//			else
				ray->t = t.x;
			return (1);
		}
		else if (t.y > 0.001 && (t.y < ray->t || ray->t <= 0.001))
		{
//			if (t.y < 0.001)
//				ray->t = 0.001;
//			else
				ray->t = t.y;
			return (-1);
		}
	}
	return(0);
}
int				ray_match(__global t_obj *o, t_ray *ray)
{
	int		i	= -1;
	int		ret	= -1;
	int		obj	= -1;

	ray->t = 0;
	while (o[++i].type != end)
	{
		switch (o[i].type) {
			case sphere :
				{
					if ((ray->imp = rt_sphere(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case plan :
				{
					if ((ray->imp = rt_plan(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case triangle :
				{
					if ((ray->imp = rt_triangle(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case cylindre :
				{
					if ((ray->imp = rt_cylindre(o, i, ray, obj)) != 0)
						ret = i;
				}
				break;
			case cone :
				{
					if ((ray->imp = rt_cone(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case para :
				{
					if ((ray->imp = rt_para(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case start_obj :
				obj = i;
				break;
			case end_obj :
				obj = -1;
				break;
		}
	}
	return (ret);
}

float4			ray_from_coord(size_t x, size_t y, __global t_cam *c)
{
	float4		ret = 0;
	ret += c->dirx * (c->p.x + ((float)x * c->viewplane.x / (float)c->size.x));
	ret += c->diry * (c->p.y - ((float)y * c->viewplane.y / (float)c->size.y));
	ret += c->dirz * (c->p.z);
	return (normalize(ret));
}

__kernel void	raytracer(
			__global int* string,
			__global t_cam *c,
			__global t_obj *o,
			__global t_obj *l,
			__global int* tex)
{
	t_ray	ray;
	size_t	i = get_global_id(0);
	size_t	j = get_global_id(1);
	int		id;
	float4	nor;
	int		lt;
	int stay;
	int pixel;
	int		refmax = 10;
	int color;
	int		old;
	int		quit;
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned char re;
	unsigned char gr;
	unsigned char bl;
	color = 0;
	float c1;
	float c2;
	float oldr;
	float oldd;
	if (i < c[0].size.x && j < c[0].size.y)
	{
		stay = 1;
		string[j * c[0].size.x + i] = 0;
		ray.dir = ray_from_coord(i, j, c);
		ray.ori = c[0].ori;
			r = 0;
			g = 0;
			b = 0;
			oldr = 1;
			stay = 0;
			quit = 0;
		while(((id = ray_match(o, &ray)) != -1) && refmax)
		{
			lt = -1;
			while(l[++lt].type == light)
			{
				color = diffuse(o, &ray.t, l, ray, id, lt, tex);
				if(stay == 0)
				{
					r = r + (((color & 0xFF0000) / 0x10000) * (o[id].diff)) > 255 ? 255 : r + (((color & 0xFF0000) / 0x10000) * (o[id].diff));
					g = g + (((color & 0xFF00) / 0x100) * (o[id].diff)) > 255 ? 255 : g + (((color & 0xFF00) / 0x100) * o[id].diff);
					b = b + (((color & 0xFF)) * (o[id].diff)) > 255 ? 255 : b + ((color & 0xFF) * o[id].diff);
				}
				if(stay != 0)
				{
//					oldr = oldr - (1 - o[id].refl) < 0 ? 0 : oldr - (1 - o[id].refl);
//					if(o[id].refl < EPSILON && o[id].diff > o[id].refl)
//					{
//						r = r + (((color & 0xFF0000) / 0x10000) * (o[id].diff * o[id].refl)) > 255 ? 255 : r + (((color & 0xFF0000) / 0x10000) * (o[id].diff * o[id].refl));
//						g = g + (((color & 0xFF00) / 0x100) * (o[id].diff * o[id].refl)) > 255 ? 255 : g + (((color & 0xFF00) / 0x100) * (o[id].diff * o[id].refl));
//						b = b + (((color & 0xFF)) * (o[id].diff * o[id].refl)) > 255 ? 255 : b + ((color & 0xFF) * (o[id].diff * o[id].refl));
//					}
//					c = clamp(c * oldr + nc * diff, 0, 255);
					(r = (((color & 0xFF0000) / 0x10000) * o[id].diff * oldr + r/* * o[id].refl*/)) > 255 ? (r = 255) : 0;
					(g = (((color & 0xFF00) / 0x100) * o[id].diff * oldr + g/* * o[id].refl*/)) > 255 ? (g = 255) : 0;
					(b = (((color & 0xFF)) * o[id].diff * oldr + b/* * o[id].refl*/)) > 255 ? (b = 255) : 0;
//					(r += (((color & 0xFF0000) / 0x10000) * (o[id].diff * oldr))) > 255 ? (r = 255) : 0;
//					g = g + (((color & 0xFF00) / 0x100) * (o[id].diff * oldr)) > 255 ? 255 : g + (((color & 0xFF00) / 0x100) * (o[id].diff * oldr));
//					b = b + (((color & 0xFF) * (o[id].diff * oldr))) > 255 ? 255 : b + ((color & 0xFF) * (o[id].diff * oldr));
//					if(oldr < EPSILON)
//					{
//					r = r + (((color & 0xFF0000) / 0x10000) * (o[id].diff)) > 255 ? 255 : r + (((color & 0xFF0000) / 0x10000) * (o[id].diff));
//					g = g + (((color & 0xFF00) / 0x100) * (o[id].diff)) > 255 ? 255 : g + (((color & 0xFF00) / 0x100) * o[id].diff);
//					b = b + (((color & 0xFF)) * (o[id].diff)) > 255 ? 255 : b + ((color & 0xFF) * o[id].diff);
//					quit = 1;
//					}
				}
			}
//			if(quit)
//				break;
			if(o[id].trans && o[id].trans > EPSILON && o[id].refl < EPSILON)
				{
					refmax--;
					ray.ori = ray.dir * ray.t + ray.ori;
//					ray.dir = ray.dir * sin(ray.ori - o[id].pos);
					c1 = dot(normalize(ray.ori - o[id].pos), (-ray.dir));
					c2 = sqrt((1 - pow(1 / 1.4, 2)) * (1 - pow(c1, 2)));
//					if(c1 > EPSILON)
//						ray.dir = ((1.0 / 1.4) * ray.dir) + ((1.0 / 1.4) * c1 - c2) * (ray.dir * ray.t + ray.ori);
//					else if(ray.imp == -1)
//						ray.dir = normalize(ray.dir * 1.4);
				}
			else if(o[id].refl && o[id].refl > EPSILON && o[id].trans < EPSILON && (o[id].type == sphere || o[id].type == plan))
				{
					refmax--;
//					if(stay == 0)
					{
						old = color;
						oldr *= o[id].refl;
						oldd = o[id].diff;
					}
//					else
//						oldr -= o[id].refl ;
					ray.ori = ray.dir * ray.t + ray.ori;
					if(o[id].type == sphere)
						ray.dir = normalize(refl(ray.dir, ray.ori - o[id].pos));
					else if(o[id].type == plan)
						ray.dir = normalize(refl(ray.dir, o[id].dir));
					stay++;
				}
			else
				break;
		}
		color = r * 0x10000 + g * 0x100 + b;
		string[j * c[0].size.x + i] = color;
	}
}

__kernel void	rng(
			__global int* in,
			__global t_cam *c,
			__global t_obj *o,
			__global int* dst,
			__global int* out)
{
	t_ray	ray;
	size_t	i = get_global_id(0);
	size_t	j = get_global_id(1);
	int		id;
	float4	nor;
	int		lt;
	int pixel;
	int color;
	float4	k;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	float		dist;
	if (i < c[0].size.x && j < c[0].size.y)
	{
		ray.dir = ray_from_coord(i, j, c);
		ray.ori = c[0].ori;
		if ((id = ray_match(o, &ray)) != -1)
		{
			lt = -1;
			k.x = (in[j * c[0].size.x + i] & 0xFF0000) / 0x10000;
			k.y = (in[j * c[0].size.x + i] & 0xFF00) / 0x100;
			k.z = (in[j * c[0].size.x + i] & 0xFF) / 0x1;
			dist = (floor(ray.t) - dst[0]);
			dist = dist < 0 ? 0 : dist;
			dist = dist > 255 ? 255 : dist;
			dist /= 255;
			float filter[filterHeight * filterWidth] =
			{
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, 0.0,
			0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0,
			0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0,
			0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0,
			0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			};
			float factor = dist;
			float bias = dist;
			for(int filterY = 0; filterY < filterHeight; filterY++)
			for(int filterX = 0; filterX < filterWidth; filterX++)
			{
				int imageX = (i - filterWidth / 2 + filterX + c[0].size.x) % c[0].size.x;
				int imageY = (j - filterHeight / 2 + filterY + c[0].size.y) % c[0].size.y;
				k.x += ((in[imageY * c[0].size.x + imageX] & 0xFF0000) / 0x10000) * filter[filterY * filterWidth + filterX];
				k.y += ((in[imageY * c[0].size.x + imageX] & 0xFF00) / 0x100) * filter[filterY * filterWidth + filterX];
				k.z += ((in[imageY * c[0].size.x + imageX] & 0xFF) / 0x1) * filter[filterY * filterWidth + filterX];
			}
			r = (unsigned char)(min(max((int)floor(factor * k.x + bias), 0), 255));
			g = (unsigned char)(min(max((int)floor(factor * k.y + bias), 0), 255));
			b = (unsigned char)(min(max((int)floor(factor * k.z + bias), 0), 255));
			
			
//			r = dist > 255 ? 255 : dist;
//			g = dist > 255 ? 255 : dist;
//			b = dist > 255 ? 255 : dist;
			color = r * 0x10000 + g * 0x100 + b;
			
			out[j * c[0].size.x + i] = color;
			//			lt = -1;
			//			if(o[id].refl > EPSILON)
			//				{
			//					nor = get_normale(ray, o, id);
			//					refl(&ray, nor);
			//				}
			//			else
			//				ref = 0;

		}
	}
}

__kernel void	cpy(
			__global int* out,
			__global int* in,
			__global int* col
					)
{
	size_t	i = get_global_id(0);
	size_t	j = get_global_id(1);
	out[j * col[0] + i] = in[j * col[0] + i];
}

__kernel void	stereo(
			__global int* red,
			__global int* vb,
			__global int* out,
			__global int* size
					)
{
	size_t	i = get_global_id(0);
	size_t	j = get_global_id(1);
	out[j * size[0] + i] = ((red[j * size[0] + i] & 0xFF0000) + (vb[j * size[0] + i] & 0x00FFFF));
}
