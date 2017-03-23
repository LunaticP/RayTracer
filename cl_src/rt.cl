#ifndef EPSILON
# define EPSILON 0.0001f
#endif

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
	light,
	start_obj,
	end_obj,
	end
}					t_type;

typedef struct 		s_obj
{
	float4			pos;
	float4			dir;	
	float4			min;
	float4			max;
	int				col;
	float			diff;
	float			refl;
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
	float4			viewplane;
	float4			p;
	float4			chunk;
}					t_cam;

typedef struct		s_ray
{
	float4			ori;
	float4			dir;
	float			t;
}					t_ray;

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
	if (d > -EPSILON && d < EPSILON)
		return (0);
	t = dot(o->pos - ray->ori, o->dir) / d;
	if (t > EPSILON && (t < ray->t || ray->t <= 0))
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

float4		norm_cone(__global t_obj *o, float4 hit, int id)
{
	float4	ret;
	float4	vec;

	vec = o[id].pos;
	if (hit.y > o[id].pos.y)
		vec.y = hit.y + tan(o[id].alpha) * sqrt(vec.x * vec.x + vec.z * vec.z);
	else
		vec.y = hit.y - tan(o[id].alpha) * sqrt(vec.x * vec.x + vec.z * vec.z);
	ret = (hit - vec);
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
	color += (((int)col.x) & 0xFF0000) / 0x10000;
	color += (((int)col.y) & 0xFF00) / 0x100;
	color += (((int)col.z) & 0xFF);
	return(color);
}

int				diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in)
{
	float4 hit;
	float4 normale;
	float4 vlight;
	int color;
	float norme;
	float dp;
	float4 fla;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char i;
	unsigned char j;
	unsigned char k;
	float rl;
	float gl;
	float bl;
	float4 mid;
	float spec;
	t_ray shad;
	int lol;
	float4 tmp;
	color = o[id].col;
	hit = ray.dir * *t + ray.ori;
	if(o[id].type == sphere)
		normale = norm_sphere(o, hit, id);
	else if (o[id].type == plan)
		normale = o[id].dir;
	else if (o[id].type == triangle)
		normale = normalize(o[id].dir);
	else if (o[id].type == cone)
		normale = norm_cone(o, hit, id);
	else if (o[id].type == cylindre)
		normale = norm_cylindre(o, hit, id);
	else
		return(color);
	vlight = l[in].pos - hit;
	shad.ori = hit;
	shad.dir = normalize(vlight);
	tmp = vlight;
		norme = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	if (((lol = ray_match(o, &shad)) != -1 && shad.t < norme) && lol != id)
		return(0);
		dp = dot(normalize(vlight), normalize(normale));
		float4 rp = dot(normalize(refl(ray.dir, normale)), vlight);

		r = (color & 0xFF0000) / 0x10000;
		g = (color & 0xFF00) / 0x100;
		b = (color & 0xFF);
		rl = (l[in].col & 0xFF0000) / 0x10000 / 255.0;
		gl = (l[in].col & 0xFF00) / 0x100 / 255.0;
		bl = (l[in].col & 0xFF) / 255.0;
		r = r * dp * (l[in].r / (norme * norme)) * rl > 255 ? 255 : r * dp * (l[in].r / (norme * norme)) * rl;
		g = g * dp * (l[in].r / (norme * norme)) * gl > 255 ? 255 : g * dp * (l[in].r / (norme * norme)) * gl;
		b = b * dp * (l[in].r / (norme * norme)) * bl > 255 ? 255 : b * dp * (l[in].r / (norme * norme)) * bl;
		ray.dir *= -1;
		mid = (normalize(ray.dir) + normalize(vlight)) / 2;
		spec = pow(dot(normalize(mid), normalize(normale)), 70);
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
	if (t > EPSILON && (t < ray->t || ray->t <= 0))
	{
		ray->t = t;
		return (d > 0 ? -1 : 1);
	}
	return (0);
}

float			sq(float a)
{
	return (a * a);
}

int				rt_cone(__global t_obj *o, t_ray *ray)
{
	float2	t;
	float	a;
	float	b;
	float	c;

	a = sq(ray->dir.x) + sq(ray->dir.z) - sq(ray->dir.y) * tan(o->alpha);
	b = -2 * ((ray->ori.x - o->pos.x) * ray->dir.x + (ray->ori.z - o->pos.z) * ray->dir.z - (ray->ori.y - o->pos.y) * ray->dir.y * tan(o->alpha));
	c = sq(ray->ori.x - o->pos.x) + sq(ray->ori.z - o->pos.z) - sq(ray->ori.y - o->pos.y) * tan(o->alpha);
	if ((quadratic(a, b, c, &t)))
	{
		if (t.x < t.y && t.x > EPSILON && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			return (1);
		}
		else if (t.y > EPSILON && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			return (-1);
		}
	}
	return (0);
}

int				rt_cylindre(__global t_obj *o, t_ray *ray)
{
	float2	t;
	float4	pos;
	t_ray	cpy;
	float4	ocpy;
	float	a;
	float	b;
	float	c;

	cpy = *ray;
	ocpy = o->pos;
	ocpy.y = 0;
	cpy.dir.y = 0;
	cpy.ori.y = 0;
	pos = ocpy - cpy.ori;
	a = dot(cpy.dir, cpy.dir);
	b = 2.0f * dot(cpy.dir, pos);
	c = dot(pos, pos) - o->r * o->r;
	if ((quadratic(a, b, c, &t)))
	{
		if (t.x < t.y && t.x > EPSILON && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			return (1);
		}
		else if (t.y > EPSILON && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			return (-1);
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
		if (t.x < t.y && t.x > EPSILON && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			return (1);
		}
		else if (t.y > EPSILON && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			return (-1);
		}
	}
	return (0);
}

float4			qt_conjugate(float4 qt)
{
	float4	ret;
	
	ret = -qt;
	ret = qt.w;
	return(ret);
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

	ret = qt_cross(qt,p);
	ret = qt_cross(ret, qt_conjugate(qt));
	return(ret);
}

int				ray_match(__global t_obj *o, t_ray *ray)
{
	int		i;
	int		ret;
	
	i = -1;
	ray->t = 0;
	ret = -1;
	while (o[++i].type != end)
	{
		switch (o[i].type) {
			case sphere :
				{
					if ((rt_sphere(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case plan :
				{
					if ((rt_plan(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case triangle :
				{
					if ((rt_triangle(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case cylindre :
				{
					if ((rt_cylindre(&(o[i]), ray)) != 0)
						ret = i;
				}
				break;
			case cone :
				{
					if ((rt_cone(&(o[i]), ray)) != 0)
						ret = i;
				}
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

__kernel void	raytracer(__global int* string, __global t_cam *c, __global t_obj *o,
	__global t_obj *l)
{
	t_ray	ray;
	size_t	i = get_global_id(0);
	size_t	j = get_global_id(1);
	int		id;
	float4	nor;
	int		lt;
	int pixel;
	int color;
	unsigned char r;
	unsigned char g;
	unsigned char b;

//	i *= c[0].;
	i *= c[0].viewplane.z;
	i += c[0].chunk.x;
	j *= c[0].viewplane.w;
	j += c[0].chunk.y;
//	j /= 2;
	if (i < c[0].size.x && j < c[0].size.y)
	{
		ray.dir = ray_from_coord(i, j, c);
		ray.ori = c[0].ori;
		if ((id = ray_match(o, &ray)) != -1)
		{
			lt = -1;
			r = 0;
			g = 0;
			b = 0;
			color = 0;
		while(l[++lt].type == light)
			{
				color = diffuse(o, &ray.t, l, ray, id, lt);
				r = r + (color & 0xFF0000) / 0x10000 > 255 ? 255 : r + (color & 0xFF0000) / 0x10000;
				g = g + (color & 0xFF00) / 0x100 > 255 ? 255 : g + (color & 0xFF00) / 0x100;
				b = b + (color & 0xFF) > 255 ? 255 : b + (color & 0xFF);
			}
			color = r * 0x10000 + g * 0x100 + b;
			string[j * c[0].size.x + i] = color;
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
