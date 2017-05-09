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
	short			tex;
	short			n_m;
	short			r_m;
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
	float2			chunk;
	short			fast;
	short			dsr;
}					t_cam;

typedef struct		s_ray
{
	float4			ori;
	float4			dir;
	float			t;
	float			t2;
	int				imp;
}					t_ray;

float4	qt_conjugate(float4 qt);
float4	qt_cross(float4 u, float4 v);
float4	qt_gen(float4 axis, float tet);
float4	qt_rot(float4 qt, float4 p);
float4	norm_sphere(__global t_obj *o, float4 hit, int id);
float4	norm_cone(__global t_obj *o, float4 hit, int id, t_ray ray);
float4	norm_cylindre(__global t_obj *o, float4 hit, int id, t_ray ray);
float4	refl(float4 ray, float4 normale);
float4	bilinear(float2 polar, __global int *tex);
float4	ray_from_coord(size_t x, size_t y, __global t_cam *c, int mul);
float	sq(float a);
int		get_light(__global t_obj *o, __global t_obj *l, float4 hit);
int		tex_num(int num, __global t_obj *o, int id, __global int *tex, float2 polar);
int		diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in, __global int *tex, float4 *n, float *rm);
int		quadratic(float a, float b, float c, float2 *ret);
int		ray_neg(__global t_obj *o, t_ray *ray, float2 *t);
int		rt_plan(__global t_obj *o, int i, t_ray *ray);
int		rt_triangle(__global t_obj *o, t_ray *ray);
int		rt_cone(__global t_obj *o, int i, int *i2, t_ray *ray);
int		rt_cylindre(__global t_obj *o, int i, int *i2, t_ray *ray);
int		rt_sphere(__global t_obj *o, int i, int *i2, t_ray *ray);
int		rt_para(__global t_obj *o, t_ray *ray);
int		ray_match(__global t_obj *o, t_ray *ray);
t_ray	rot_ray(t_ray from, float tet, float phi, float4 center);

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
	float	plot;

	plot = ((hit.x - o[id].pos.x) + (hit.y - o[id].pos.y) + (hit.z - o[id].pos.z)) / 3.0f;

	dir = normalize(o[id].dir * (plot > 0 ? 1.0f : -1.0f));
	k = tan(o[id].alpha * M_PI / 180.0f);
	m = dot(normalize(ray.dir), dir) * ray.t + dot(ray.ori - o[id].pos, dir);
	ret = normalize(hit - o[id].pos - (1.0f + k * k) * dir * m);
	return(ret);
}

float4		norm_cylindre(__global t_obj *o, float4 hit, int id, t_ray ray)
{
	float4	ret;
	float4	dir;
	float	m;

	dir = normalize(o[id].dir);
	m = dot(normalize(ray.dir), dir) * ray.t + dot(ray.ori - o[id].pos, dir);
	ret = normalize(hit - o[id].pos - dir * m);
	return(ret);
}

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
	//	if(nb); 
	col /= nb;
	color += (((int)col.x) &  0xFF0000) / 0x10000;
	color += (((int)col.y) & 0xFF00) / 0x100;
	color += (((int)col.z) & 0xFF);
	return(color);
}

float4			bilinear(float2 polar, __global int *tex)
{
	float4	ir;
	float4	ig;
	float4	ib;
	float4	out;

	ir.x = ((int)polar.x * tex[1] + ((int)polar.y + 1) < tex[0]) ? \
		   (float)((tex[(int)polar.x * tex[1] + ((int)polar.y + 1)] & 0xFF0000) / 0x10000) : 255;
	ir.y = ((int)(polar.x + 1) * tex[1] + ((int)polar.y + 1) < tex[0]) ? \
		   (float)((tex[(int)(polar.x + 1) * tex[1] + ((int)polar.y + 1)] & 0xFF0000) / 0x10000) : 255;
	ir.z = ((int)polar.x * tex[1] + (int)polar.y < tex[0]) ? \
		   (float)((tex[(int)polar.x * tex[1] + (int)polar.y] & 0xFF0000) / 0x10000) : 255;
	ir.w = ((int)(polar.x + 1) * tex[1] + (int)polar.y < tex[0]) ? \
		   (float)((tex[(int)(polar.x + 1) * tex[1] + (int)polar.y] & 0xFF0000) / 0x10000) : 255;
	ig.x = ((int)polar.x * tex[1] + ((int)polar.y + 1) < tex[0]) ? \
		   (float)((tex[(int)polar.x * tex[1] + ((int)polar.y + 1)] & 0xFF00) / 0x100) : 255;
	ig.y = ((int)(polar.x + 1) * tex[1] + ((int)polar.y + 1) < tex[0]) ? \
		   (float)((tex[(int)(polar.x + 1) * tex[1] + ((int)polar.y + 1)] & 0xFF00) / 0x100) : 255;
	ig.z = ((int)polar.x * tex[1] + (int)polar.y < tex[0]) ? \
		   (float)((tex[(int)polar.x * tex[1] + (int)polar.y] & 0xFF00) / 0x100) : 255;
	ig.w = ((int)(polar.x + 1) * tex[1] + (int)polar.y < tex[0]) ? \
		   (float)((tex[(int)(polar.x + 1) * tex[1] + (int)polar.y] & 0xFF00) / 0x100) : 255;
	ib.x = ((int)polar.x * tex[1] + ((int)polar.y + 1) < tex[0]) ? \
		   (float) (tex[(int)polar.x * tex[1] + ((int)polar.y + 1)] & 0xFF) : 255;
	ib.y = ((int)(polar.x + 1) * tex[1] + ((int)polar.y + 1) < tex[0]) ? \
		   (float) (tex[(int)(polar.x + 1) * tex[1] + ((int)polar.y + 1)] & 0xFF) : 255;
	ib.z = ((int)polar.x * tex[1] + (int)polar.y < tex[0]) ? \
		   (float) (tex[(int)polar.x * tex[1] + (int)polar.y] & 0xFF) : 255;
	ib.w = ((int)(polar.x + 1) * tex[1] + (int)polar.y < tex[0]) ? \
		   (float) (tex[(int)(polar.x + 1) * tex[1] + (int)polar.y] & 0xFF) : 255;
	ir.x = (ceil(polar.x) - polar.x) / (ceil(polar.x) - floor(polar.x)) * ir.x + \
		   (polar.x - floor(polar.x)) / (ceil(polar.x) - floor(polar.x)) * ir.y;
	ir.y = (ceil(polar.x) - polar.x) / (ceil(polar.x) - floor(polar.x)) * ir.z + \
		   (polar.x - floor(polar.x)) / (ceil(polar.x) - floor(polar.x)) * ir.w;
	out.x = (ceil(polar.y) - polar.y) / (ceil(polar.y) - floor(polar.y)) * ir.y + \
			(polar.y - floor(polar.y)) / (ceil(polar.y) - floor(polar.y)) * ir.x;
	ig.x = (ceil(polar.x) - polar.x) / (ceil(polar.x) - floor(polar.x)) * ig.x + \
		   (polar.x - floor(polar.x)) / (ceil(polar.x) - floor(polar.x)) * ig.y;
	ig.y = (ceil(polar.x) - polar.x) / (ceil(polar.x) - floor(polar.x)) * ig.z + \
		   (polar.x - floor(polar.x)) / (ceil(polar.x) - floor(polar.x)) * ig.w;
	out.y = (ceil(polar.y) - polar.y) / (ceil(polar.y) - floor(polar.y)) * ig.y + \
			(polar.y - floor(polar.y)) / (ceil(polar.y) - floor(polar.y)) * ig.x;
	ib.x = (ceil(polar.x) - polar.x) / (ceil(polar.x) - floor(polar.x)) * ib.x + \
		   (polar.x - floor(polar.x)) / (ceil(polar.x) - floor(polar.x)) * ib.y;
	ib.y = (ceil(polar.x) - polar.x) / (ceil(polar.x) - floor(polar.x)) * ib.z + \
		   (polar.x - floor(polar.x)) / (ceil(polar.x) - floor(polar.x)) * ib.w;
	out.z = (ceil(polar.y) - polar.y) / (ceil(polar.y) - floor(polar.y)) * ib.y + \
			(polar.y - floor(polar.y)) / (ceil(polar.y) - floor(polar.y)) * ib.x;
	return (out);
}

int				tex_num(int num, __global t_obj *o, int id, __global int *tex, float2 polar)
{
	int	i;
	int j;
	int out;

	i = 1;
	j = 1;
	out = 0;
	while (i < num && j + 3 < tex[0])
	{
		j += tex[j] * tex[j + 1] + 2;
		i++;
	}
	if (o[id].type == sphere)
	{
		out = (int)(polar.x * (float)tex[j + 1] / M_PI) * tex[j] \
			  + (int)(polar.y * (float)tex[j] / M_PI) + j + 2;
	}
	if (o[id].type == plan)
	{
		out = (int)((polar.x / 10) * (float)tex[j + 1]) % tex[j + 1] * tex[j] \
			  + (int)((polar.y / 10) * (float)tex[j]) + j + 2;
	}
	if (o[id].type == cone || o[id].type == cylindre)
	{
		out = abs((int)(polar.x / 5 * (float)tex[j + 1]) % tex[j + 1]) * tex[j] \
			  + (int)(polar.y * tex[j] / M_PI) % tex[j] + j + 2;
	}
	return (out > tex[0] || out < 0 ? 0 : out);
}

int				diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in, __global int *tex, float4 *n, float *rm)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	i;
	unsigned char	j;
	unsigned char	k;
	float4			hit;
	float4			normale;
	float4			vlight;
	float4			fla;
	float4			mid;
	float4			tmp;
	float4			angle;
	float4			temp;
	float4			ctsn;
	float4			axis;
	float2			polar;
	float			norme;
	float			dp;
	float			spec;
	float			rl;
	float			gl;
	float			bl;
	int				lol;
	int				color;
	t_ray			shad;

	color = o[id].col;
	hit = ray.dir * *t + ray.ori;
	temp = normalize(o[id].dir);
	angle = acos(dot(temp, (float4)(0,1,0,0)));
	axis = normalize(cross(temp, (float4)(0,1,0,0)));
	ctsn = hit - o[id].pos;
	ctsn = ctsn * cos(angle) + cross(axis, ctsn) * sin(angle) + axis * dot(axis, ctsn) * (1 - cos(angle));
	if(o[id].type == sphere)
	{
		normale = norm_sphere(o, hit, id);
		polar.x = (atan(-ctsn.y / sqrt(ctsn.z * ctsn.z + ctsn.x * ctsn.x))) + M_PI_2_F;
		polar.y = (atan(ctsn.x / -ctsn.z)) + M_PI_2_F;
	}
	else if (o[id].type == plan)
	{
		polar.x = fabs(ctsn.x + 15);
		polar.y = fabs(ctsn.z + 15);
		normale = o[id].dir;
	}
	else if (o[id].type == cone)
	{
		normale = norm_cone(o, hit, id, ray);
		polar.x = ctsn.y;
		polar.y = atan(ctsn.x / ctsn.z) + M_PI_2_F;
	}
	else if (o[id].type == cylindre)
	{
		normale = norm_cylindre(o, hit, id, ray);
		polar.x = ctsn.y;
		polar.y = (atan(ctsn.x / -ctsn.z)) + M_PI_2_F;
	}
	else if (o[id].type == para)
		normale = hit - o[id].pos;
	if (o[id].n_m)
	{
		color = tex[tex_num(o[id].n_m, o, id, tex, polar)];
		normale.x += (color & 0xFF0000 / 0x10000) / 128.0 - 1.0;
		normale.y += (color & 0xFF00 / 0x100) / 128.0 - 1.0;
		normale.z += (color & 0xFF) / 128.0 - 2.0;
	}
	if (o[id].r_m)
	{
		color = tex[tex_num(o[id].r_m, o, id, tex, polar)];
		*rm = (float)((color & 0xFF0000) / 0x10000 + (color & 0xFF00) / 0x100 + (color & 0xFF)) / 765.0f;
	}
	if (o[id].tex)
		color = tex[tex_num(o[id].tex, o, id, tex, polar)];
	else
		color = o[id].col;
	if (o[id].pos.w > 0.5f)
		normale *= -1.0f;
	*n = normale;
	vlight = l[in].pos - hit;
	shad.ori = hit;
	shad.dir = normalize(vlight) * (o[id].pos.w < 0.5f ? 1.0f : -1.0f);
	tmp = vlight;
	norme = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	r = (color & 0xFF0000) / 0x10000;
	g = (color & 0xFF00) / 0x100;
	b = (color & 0xFF);
	if ((lol = ray_match(o, &shad)) != -1 && shad.t < norme && o[id].pos.w < 0.5f)
	{
		//		if (o[id].pos.w > 0.5f)
		//			return (o[lol].col);
		r /= 50;
		g /= 50;
		b /= 50;
		return(r * 0x10000 + g * 0x100 + b);
	}
	dp = dot(normalize(vlight), normalize(normale));
	rl = (l[in].col & 0xFF0000) / 0x10000 / 255.0;
	gl = (l[in].col & 0xFF00) / 0x100 / 255.0;
	bl = (l[in].col & 0xFF) / 255.0;
	r = r * dp * (l[in].r / (norme * norme)) * rl > 255 ? 255 : r * dp * (l[in].r / (norme * norme)) * rl + r / 50;
	g = g * dp * (l[in].r / (norme * norme)) * gl > 255 ? 255 : g * dp * (l[in].r / (norme * norme)) * gl + g / 50;
	b = b * dp * (l[in].r / (norme * norme)) * bl > 255 ? 255 : b * dp * (l[in].r / (norme * norme)) * bl + b / 50;
	mid = (normalize(-ray.dir) + normalize(vlight)) / 2;
	spec = pow(dot(normalize(mid), normalize(normale)) / 1.005, 100);
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

int				ray_neg(__global t_obj *o, t_ray *ray, float2 *t)
{
	t_ray	ray2;
	int		i;
	int		ret;

	i = -1;
	ray2.t = 0;
	ray2.ori = ray->ori;
	ray2.dir = ray->dir;
	ret = 1;
	while (o[++i].type != end)
	{
		if (o[i].pos.w > 0.5f)
		{
			switch (o[i].type)
			{
				case sphere :
					{
						if ((rt_sphere(o, i, (int *)0, &ray2)) != 0)
						{
							if (t->x == t->y)
							{
								if(t->x > ray2.t && t->y < ray2.t2)
									ret = -1;
								break;
							}
							else if (ray2.t <= t->x && ray2.t2 >= t->x && ray2.t2 <= t->y)
							{
								t->x = ray2.t2;
								t->y = ray2.t2;
								ret = i + 1;
							}
							else if (ray2.t < t->x && ray2.t2 > t->y)
								ret = 0;
							else
								ret = -1;
						}
					}
					break;
				case cylindre :
					{
						if ((rt_cylindre(o, i, (int *)0, &ray2)) != 0)
						{
							if (t->x == t->y)
							{
								if(t->x > ray2.t && t->y < ray2.t2)
									ret = -1;
								break;
							}
							else if (ray2.t <= t->x && ray2.t2 >= t->x && ray2.t2 <= t->y)
							{
								t->x = ray2.t2;
								t->y = ray2.t2;
								ret = i + 1;
							}
							else if (ray2.t < t->x && ray2.t2 > t->y)
								ret = 0;
							else
								ret = -1;
						}
					}
					break;
				case cone :
					{
						if ((rt_cone(o, i, (int *)0, &ray2)) != 0)
						{
							if (t->x == t->y)
							{
								if(t->x > ray2.t && t->y < ray2.t2)
									ret = -1;
								break;
							}
							else if (ray2.t <= t->x && ray2.t2 >= t->x && ray2.t2 <= t->y)
							{
								t->x = ray2.t2;
								t->y = ray2.t2;
								ret = i + 1;
							}
							else if (ray2.t < t->x && ray2.t2 > t->y)
								ret = 0;
							else
								ret = -1;
						}
					}
					break;
				default :
					break;
			}
		}
	}
	return (ret); 
}

int				rt_plan(__global t_obj *o, int i, t_ray *ray)
{
	float	d = dot(o[i].dir, ray->dir);
	float2	t;

	// ray paralele au plan
	if (d > -EPSILON && d < EPSILON)
		return (0);
	t.x = dot(o[i].pos + EPSILON - ray->ori, o[i].dir) / d;
	t.y = t.x;
	if (t.x > EPSILON && (t.x < ray->t || ray->t <= EPSILON)
			&& ray_neg(o, ray, &t) > 0)
	{
		ray->t = t.x;
		return (d > 0 ? -1 : 1);
	}
	return (0);
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

int				rt_cone(__global t_obj *o, int i, int *i2, t_ray *ray)
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
	odir = normalize(o[i].dir);
	x = ray->ori - o[i].pos;
	k = tan(o[i].alpha / 360.0 * M_PI);
	k = 1.0 + k * k;
	a = dot(d, d) - sq(dot(d, odir)) * k;
	b = (dot(d, x) - k * dot(d, odir) * dot(x, odir)) * -2.0;
	c = dot(x, x) - k * sq(dot(x, odir));
	if (quadratic(a, b, c, &t) && !(a = 0) && (o[i].pos.w > 0.5f || (a = ray_neg(o, ray, &t)) != 0))
	{
		if (o[i].pos.w < 0.5f)
			*i2 = a - 1;
		if (t.x < t.y && (o[i].pos.w > 0.5f || t.x > 0.01f) && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if ((o[i].pos.w > 0.5f || t.y > 0.01f) && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			ray->t2 = t.x;
			return (-1);
		}
	}
	return (0);
}

int				rt_cylindre(__global t_obj *o, int i, int *i2, t_ray *ray)
{
	float2	t;
	float	a;
	float	b;
	float	c;
	float4	odir;
	float4	d;
	float4	x;

	d = normalize(ray->dir);
	odir = normalize(o[i].dir);
	x = ray->ori - o[i].pos;
	a = dot(d, d) - sq(dot(d, odir));
	b = (dot(d, x) - dot(d, odir) * dot(x, odir)) * -2.0f;
	c = dot(x, x) - sq(dot(x, odir)) - o[i].r * o[i].r;
	if (quadratic(a, b, c, &t) && !(a = 0) && (o[i].pos.w > 0.5f || (a = ray_neg(o, ray, &t)) != 0))
	{
		if (o[i].pos.w < 0.5f)
			*i2 = a - 1;
		if (t.x < t.y && (o[i].pos.w > 0.5f || t.x > 0.01) && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if ((o[i].pos.w > 0.5f || t.y > 0.01) && (t.y < ray->t || ray->t <= 0))
		{
			ray->t = t.y;
			ray->t2 = t.x;
			return (-1);
		}
	}
	return (0);
}

int				rt_sphere(__global t_obj *o, int i, int *i2, t_ray *ray)
{
	float2	t;
	float4	pos;
	float	a;
	float	b;
	float	c;

	pos = o[i].pos - ray->ori;
	a = dot(ray->dir, ray->dir);
	b = 2.0f * dot(ray->dir, pos);
	c = dot(pos, pos) - o[i].r * o[i].r;
	if (quadratic(a, b, c, &t) && !(a = 0) && (o[i].pos.w > 0.5f || (a = ray_neg(o, ray, &t)) != 0))
	{
		if (o[i].pos.w < 0.5f)
			*i2 = a - 1;
		if (t.x < t.y && (o[i].pos.w > 0.5f || t.x > 0.001) && (t.x < ray->t || ray->t <= 0.001))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if ((o[i].pos.w > 0.5f || t.y > 0.001) && (t.y < ray->t || ray->t <= 0.001))
		{
			ray->t = t.y;
			ray->t2 = t.x;
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
	pos = rcp.ori - opos;
	//	float4	k = dot(pos, o->dir);
	a = dot(rcp.dir, rcp.dir) - pow(dot(rcp.dir, o->dir), 2);
	b = 2.0f * (dot(rcp.dir, pos) - dot(rcp.dir, o->dir));// * (dot(pos, o->dir) + 2 * k));
	c = dot(pos, pos) - dot(pos, o->dir) * (dot(pos, o->dir));// + 4 * k);
	if ((quadratic(a, b, c, &t)))
	{
		if (t.x < t.y && t.x > 0.001 && (t.x < ray->t || ray->t <= 0.001))
		{
			ray->t = t.x;
			return (1);
		}
		else if (t.y > 0.001 && (t.y < ray->t || ray->t <= 0.001))
		{
			ray->t = t.y;
			return (-1);
		}
	}
	return(0);
}

int				ray_match(__global t_obj *o, t_ray *ray)
{
	int		i = -1;
	int		i2 = -1;
	int		ret = -1;

	ray->t = 0;
	while (o[++i].type != end)
	{
		if (o[i].pos.w < 0.5f)
		{
			switch (o[i].type)
			{
				case sphere :
					{
						if ((ray->imp = rt_sphere(o, i, &i2, ray)) != 0)
							ret = (i2 > 0) ? i2 : i;
					}
					break;
				case plan :
					{
						if ((ray->imp = rt_plan(o, i, ray)) != 0)
							ret = i;
					}
					break;
				case cylindre :
					{
						if ((ray->imp = rt_cylindre(o, i, &i2, ray)) != 0)
							ret = (i2 > 0) ? i2 : i;
					}
					break;
				case cone :
					{
						if ((ray->imp = rt_cone(o, i, &i2, ray)) != 0)
							ret = (i2 > 0) ? i2 : i;
					}
					break;
				case para :
					{
						if ((ray->imp = rt_para(&(o[i]), ray)) != 0)
							ret = i;
					}
				default :
					break;
			}
		}
	}
	return (ret);
}

float4			ray_from_coord(size_t x, size_t y, __global t_cam *c, int mul)
{
	float4		ret = 0;
	ret += c->dirx * (c->p.x + ((float)x * c->viewplane.x / (float)c->size.x * mul));
	ret += c->diry * (c->p.y - ((float)y * c->viewplane.y / (float)c->size.y * mul));
	ret += c->dirz * (c->p.z);
	return ((ret)); 
}

__kernel void	raytracer(
		__global int* string,
		__global t_cam *c,
		__global t_obj *o,
		__global t_obj *l,
		__global int* tex)
{
	t_ray	ray; 
	t_ray	tmp;
	size_t			i = get_global_id(0);
	size_t			j = get_global_id(1);
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
	float4			nor;
	float			oldr;
	float			oldd;
	float			rm;
	int				id;
	int				lt;
	int				stay;
	int				refmax = 7;
	int				color = 0;
	int				old;
	int				quit;

	i *= c[0].viewplane.z;
	i += c[0].chunk.x;
	j *= c[0].viewplane.z;
	j += c[0].chunk.y;
	if (i < (size_t)c[0].size.x && j < (size_t)c[0].size.y)
	{
		string[j * c[0].size.x + i] = 0;
		ray.dir = normalize(ray_from_coord(i, j, c, 1));
		ray.ori = c[0].ori;
		r = 0;
		g = 0;
		b = 0;
		stay = 1;
		oldr = 1;
		stay = 0;
		quit = 0;
		while(((id = ray_match(o, &ray)) != -1) && refmax)
		{
			lt = -1;
			while(l[++lt].type == light)
			{
				color = diffuse(o, &ray.t, l, ray, id, lt, tex, &nor, &rm);
				if(stay == 0)
				{
					r = r + (((color & 0xFF0000) / 0x10000) * (o[id].diff)) > 255 ?
						255 : r + (((color & 0xFF0000) / 0x10000) * (o[id].diff));
					g = g + (((color & 0xFF00) / 0x100) * (o[id].diff)) > 255 ?
						255 : g + (((color & 0xFF00) / 0x100) * o[id].diff);
					b = b + (((color & 0xFF)) * (o[id].diff)) > 255 ?
						255 : b + ((color & 0xFF) * o[id].diff);
				}
				if(stay != 0)
				{
					(r = (((color & 0xFF0000) / 0x10000) * o[id].diff * oldr + r)) > 255 ? (r = 255) : 0;
					(g = (((color & 0xFF00) / 0x100) * o[id].diff * oldr + g)) > 255 ? (g = 255) : 0;
					(b = (((color & 0xFF)) * o[id].diff * oldr + b)) > 255 ? (b = 255) : 0;
				}
			}
			if(o[id].trans && o[id].trans > EPSILON && o[id].refl < EPSILON)
			{
				refmax--;
				ray.ori = ray.dir * ray.t + ray.ori;
			}
			else if(o[id].refl && o[id].refl > EPSILON && o[id].trans < EPSILON)
			{
				refmax--;
				old = color;
				oldr *= (o[id].r_m > 0 ? rm * o[id].refl : o[id].refl);
				oldd = o[id].diff;
				tmp = ray;
				ray.ori = ray.dir * ray.t + ray.ori;
				ray.dir = normalize(refl(ray.dir, nor));
				stay++;
			}
			else
				break;
		}
		color = r * 0x10000 + g * 0x100 + b;
		string[j * c[0].size.x + i] = color;
	}
}

__kernel void	rt_fast(
		__global int* string,
		__global t_cam *c,
		__global t_obj *o)
{
	t_ray			ray;
	size_t			i = get_global_id(0) * 2;
	size_t			j = get_global_id(1) * 2;
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
	int				id;
	int				color;

	if (i < (size_t)c[0].size.x && j < (size_t)c[0].size.y)
	{
		string[j * c[0].size.x + i] = 0;
		ray.dir = normalize(ray_from_coord(i, j, c, c[0].dsr));
		ray.ori = c[0].ori;
		if ((id = ray_match(o, &ray)) != -1)
		{
			r = ((o[id].col & 0xFF0000) / 0x10000) / ray.t * 4;
			g = ((o[id].col & 0x00FF00) / 0x00100) / ray.t * 4;
			b = ((o[id].col & 0x0000FF) / 0x00001) / ray.t * 4;
			r = r > 255 ? 255 : r;
			g = g > 255 ? 255 : g;
			b = b > 255 ? 255 : b;
			color = r * 0x10000 + g * 0x100 + b;
			string[j * c[0].size.x + i] = color;
			string[j * c[0].size.x + i + 1] = color;
			string[(j + 1) * c[0].size.x + i] = color;
			string[(j + 1) * c[0].size.x + i + 1] = color;
		}
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
	size_t			i = get_global_id(0);
	size_t			j = get_global_id(1);
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	float4			k;
	float			dist;
	int				color;
	int				id;
	int				lt;
	if (i < (size_t)c[0].size.x && j < (size_t)c[0].size.y)
	{
		ray.dir = ray_from_coord(i, j, c, 1);
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
			color = r * 0x10000 + g * 0x100 + b;
			out[j * c[0].size.x + i] = color;
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
