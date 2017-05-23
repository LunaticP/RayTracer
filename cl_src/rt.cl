#ifndef EPSILON
# define EPSILON 0.00001f
#endif

#if __OPENCL_VERSION__ < 120
# define COS cosf
#else
# define COS cos
#endif

typedef enum		e_type
{
	plan,
	sphere,
	cylindre,
	cone,
	light,
	end
}					t_type;

typedef struct 		s_obj
{
	float4			pos;
	float4			dir;
	float4			min;
	float4			max;
	float4			mod_tex;
	float4			mod_normal;
	float4			mod_ref;
	float4			mod_trans;
	float			diff;
	float			refl;
	float			trans;
	float			r;
	float			alpha;
	int				col;
	short			tex;
	short			n_m;
	short			r_m;
	short			t_m;
	t_type			type;
}					t_obj;

typedef struct		s_cam
{
	float4			ori;
	float4			dirx;
	float4			diry;
	float4			dirz;
	float4			rot;
	int2			size;
	float4			viewplane;
	float4			p;
	float2			chunk;
	short			fast;
	short			dsr;
	int				ambient;
}					t_cam;

typedef struct		s_ray
{
	float4			ori;
	float4			dir;
	float			t;
	float			t2;
	int				imp;
}					t_ray;

float4	norm_sphere(__global t_obj *o, float4 hit, int id);
float4	norm_cone(__global t_obj *o, float4 hit, int id, t_ray ray);
float4	norm_cylindre(__global t_obj *o, float4 hit, int id, t_ray ray);
float4	refl(float4 ray, float4 normale);
float4	bilinear(float2 polar, __global int *tex);
float4	ray_from_coord(size_t x, size_t y, __global t_cam *c, int mul);
float	sq(float a);
int		get_light(__global t_obj *o, __global t_obj *l, float4 hit);
int		tex_num(int num, __global t_obj *o, int id, __global int *tex, float2 polar, float4 tile);
int		diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in, __global int *tex, float4 *n, float *rm, float *tm);
int		quadratic(float a, float b, float c, float2 *ret);
int		ray_neg(__global t_obj *o, t_ray *ray, float2 *t);
int		rt_plan(__global t_obj *o, int i, t_ray *ray);
int		rt_cone(__global t_obj *o, int i, int *i2, t_ray *ray);
int		rt_cylindre(__global t_obj *o, int i, int *i2, t_ray *ray);
int		rt_sphere(__global t_obj *o, int i, int *i2, t_ray *ray);
int		rt_para(__global t_obj *o, t_ray *ray);
int		ray_match(__global t_obj *o, t_ray *ray);
int		limit(__global t_obj *o, float4 hit, int id);

float			sq(float a)
{
	return (a * a);
}

int				limit(__global t_obj *o, float4 hit, int id)
{
	return(((hit.x > o[id].max.x ||
			hit.y > o[id].max.y ||
			hit.z > o[id].max.z) && o[id].max.w > 0.5) ||
			((hit.x < o[id].min.x ||
			hit.y < o[id].min.y ||
			hit.z < o[id].min.z) && o[id].min.w > 0.5));
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

int				tex_num(int num, __global t_obj *o, int id, __global int *tex, float2 polar, float4 tile)
{
	int	i;
	int j;
	int out;
	int2	pol;

	i = 1;
	j = 1;
	out = 0;
	polar.x += tile.z;
	polar.y += tile.w;
	while (i < num && j + 3 < tex[0])
	{
		j += tex[j] * tex[j + 1] + 2;
		i++;
	}
	if (o[id].type == sphere)
	{
		pol.x = (int)((polar.x * tile.x) * (float)tex[j + 1] / M_PI) % tex[j + 1];
		pol.y = (int)((polar.y * tile.y) * (float)tex[j] / M_PI) % tex[j];
	}
	else if (o[id].type == plan)
	{
		pol.x = (int)(polar.x / tile.x * (float)tex[j + 1]) % tex[j + 1];
		pol.y = (int)(polar.y / tile.y * (float)tex[j]) % tex[j];
	}
	else if (o[id].type == cone || o[id].type == cylindre)
	{
		pol.x = (int)(polar.x / tile.x * (float)tex[j + 1]) % tex[j + 1];
		pol.y = (int)((polar.y * tile.y) * (float)tex[j] / M_PI) % tex[j];
	}
	else
		out = 0;
	out = pol.x * tex[j] + pol.y + j + 2;
	return (out > tex[0] || out < 0 ? 0 : out);
}

int				diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in, __global int *tex, float4 *n, float *rm, float *tm)
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
		polar.x = ctsn.x + 15;
		polar.y = ctsn.z + 15;
		normale = o[id].dir;
	}
	else if (o[id].type == cone)
	{
		normale = norm_cone(o, hit, id, ray);
		polar.x = fabs(ctsn.y);
		polar.y = atan(ctsn.x / ctsn.z) + M_PI_2_F;
	}
	else if (o[id].type == cylindre)
	{
		normale = norm_cylindre(o, hit, id, ray);
		polar.x = fabs(ctsn.y);
		polar.y = (atan(ctsn.x / -ctsn.z)) + M_PI_2_F;
	}
	if (o[id].n_m)
	{
		color = tex[tex_num(o[id].n_m, o, id, tex, polar, o[id].mod_normal)];
		normale.x += (color & 0xFF0000 / 0x10000) / 128.0 - 1.0;
		normale.y += (color & 0xFF00 / 0x100) / 128.0 - 1.0;
		normale.z += (color & 0xFF) / 128.0 - 2.0;
	}
	if (o[id].r_m)
	{
		color = tex[tex_num(o[id].r_m, o, id, tex, polar, o[id].mod_ref)];
		*rm = (float)((color & 0xFF0000) / 0x10000 + (color & 0xFF00) / 0x100 + (color & 0xFF)) / 765.0f;
	}
	if (o[id].t_m)
	{
		color = tex[tex_num(o[id].t_m, o, id, tex, polar, o[id].mod_trans)];
		*tm = (float)((color & 0xFF0000) / 0x10000 + (color & 0xFF00) / 0x100 + (color & 0xFF)) / 765.0f;
	}
	if (o[id].tex)
		color = tex[tex_num(o[id].tex, o, id, tex, polar, o[id].mod_tex)];
	else
		color = o[id].col;
	if (o[id].pos.w > 0.5f || ray.imp == -1)
		normale *= -1.0f;
	*n = normale;
	if(l[in].pos.w < 0.5)
		vlight = l[in].pos - hit;
	else
	{
		vlight = -l[in].pos;
		vlight.w = 0.0;
		vlight = normalize(vlight);
	}
	shad.ori = hit;
	shad.dir = normalize(vlight) * (o[id].pos.w < 0.5f ? 1.0f : -1.0f);
	tmp = vlight;
	norme = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	r = (color & 0xFF0000) / 0x10000;
	g = (color & 0xFF00) / 0x100;
	b = (color & 0xFF);
	if ((lol = ray_match(o, &shad)) != -1 && shad.t < norme && o[id].pos.w < 0.5f)
	{
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

	float4 point = t.x * ray->dir + ray->ori - o[i].pos;
	float4 temp = normalize(o[i].dir);
	float angle = acos(dot(temp, (float4)(0.0f,1.0f,0.0f,0.0f)));
	float4 axis = normalize(cross(temp, (float4)(0.0f,1.0f,0.0f,0.0f)));
	point = point * cos(angle) + cross(axis, point) * sin(angle) + axis * dot(axis, point) * (1 - cos(angle));

	if ((t.x > EPSILON && (t.x < ray->t || ray->t <= EPSILON)
			&& ray_neg(o, ray, &t) > 0) && !limit(o, point, i))
	{
		ray->t = t.x;
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
		if(t.x > 0.1f)
		{
			ray->t = t.x;
			return(1);
		}
		if(t.y > 0.1f && (t.y < t.x || t.x < 0.1f))
		{
			ray->t = t.y;
			return(-1);
		}
/*		if ((t.x < t.y && (o[i].pos.w > 0.5f || t.x > 0.01f) && (t.x < ray->t || ray->t <= 0)))
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
		}*/
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
	float4 point = (t.x * ray->dir + ray->ori) - o[i].pos;
	float4 point2 = (t.y * ray->dir + ray->ori) - o[i].pos;
	float4 temp = normalize(o[i].dir);
	float angle = acos(dot(temp, (float4)(0.0f,1.0f,0.0f,0.0f)));
	float4 axis = normalize(cross(temp, (float4)(0.0f,1.0f,0.0f,0.0f)));
	point = point * cos(angle) + cross(axis, point) * sin(angle) + axis * dot(axis, point) * (1 - cos(angle));
	point2 = point2 * cos(angle) + cross(axis, point2) * sin(angle) + axis * dot(axis, point2) * (1 - cos(angle));
		if (o[i].pos.w < 0.5f)
			*i2 = a - 1;
		if ((t.x < t.y && (o[i].pos.w > 0.5f || t.x > 0.01) && (t.x < ray->t || ray->t <= 0)) && !limit(o, point, i))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if (((o[i].pos.w > 0.5f || t.y > 0.01) && (t.y < ray->t || ray->t <= 0)) && !limit(o, point2, i))
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
	float4 point = (t.x * ray->dir + ray->ori) - o[i].pos;
	float4 point2 = (t.y * ray->dir + ray->ori) - o[i].pos;
	float4 temp = normalize(o[i].dir);
	float angle = acos(dot(temp, (float4)(0.0f,1.0f,0.0f,0.0f)));
	float4 axis = normalize(cross(temp, (float4)(0.0f,1.0f,0.0f,0.0f)));
	point = point * cos(angle) + cross(axis, point) * sin(angle) + axis * dot(axis, point) * (1 - cos(angle));
	point2 = point2 * cos(angle) + cross(axis, point2) * sin(angle) + axis * dot(axis, point2) * (1 - cos(angle));
		if (o[i].pos.w < 0.5f)
			*i2 = a - 1;
		if ((t.x < t.y && (o[i].pos.w > 0.5f || t.x > 0.001) && (t.x < ray->t || ray->t <= 0.001)) && !limit(o, point, i))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if (((o[i].pos.w > 0.5f || t.y > 0.001) && (t.y < ray->t || ray->t <= 0.001))&& !limit(o, point2, i))
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
				case end :
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
	t_ray			ray; 
	t_ray			tmp;
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
	size_t			i = get_global_id(0);
	size_t			j = get_global_id(1);
	float4			nor;
	float			oldr;
	float			oldd;
	float			rm;
	float			tm;
	int				id;
	int				lt;
	int				stay;
	int				refmax = 7;
	int				color = 0;
	int				old;
	int				quit;

	i *= c[0].viewplane.z;
	i += c[0].chunk.x;
	j *= c[0].viewplane.w;
	j += c[0].chunk.y;
	if (i < (size_t)c[0].size.x && j < (size_t)c[0].size.y)
	{
		string[j * c[0].size.x + i] = 0xFF00FF;
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
				color = diffuse(o, &ray.t, l, ray, id, lt, tex, &nor, &rm, &tm);
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
				oldr *= (o[id].t_m > 0 ? tm * o[id].trans : o[id].trans);
				r *= (o[id].t_m > 0 ? 1 - tm : 1 - o[id].trans);
				g *= (o[id].t_m > 0 ? 1 - tm : 1 - o[id].trans);
				b *= (o[id].t_m > 0 ? 1 - tm : 1 - o[id].trans);
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
			{
				r = r + (((c[0].ambient & 0xFF0000) / 0x10000) * (o[id].diff)) > 255 ?
				255 : r + (((c[0].ambient & 0xFF0000) / 0x10000) * (o[id].diff));
				g = g + (((c[0].ambient & 0xFF00) / 0x100) * (o[id].diff)) > 255 ?
				255 : g + (((c[0].ambient & 0xFF00) / 0x100) * o[id].diff);
				b = b + (((c[0].ambient & 0xFF)) * (o[id].diff)) > 255 ?
				255 : b + ((c[0].ambient & 0xFF) * o[id].diff);
				break;
			}
		}
		color = r * 0x10000 + g * 0x100 + b;
		string[j * c[0].size.x + i] = color;
	}
}

__kernel void	rt_fast(
		__global int* string,
		__global t_cam *c,
		__global t_obj *o,
		__global int *m_id,
		__global int *obj_id)
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
			r = ((o[id].col & 0xFF0000) / 0x10000) / ray.t * 9;
			g = ((o[id].col & 0x00FF00) / 0x00100) / ray.t * 9;
			b = ((o[id].col & 0x0000FF) / 0x00001) / ray.t * 9;
			r = r > 255 ? 255 : r;
			g = g > 255 ? 255 : g;
			b = b > 255 ? 255 : b;
			color = r * 0x10000 + g * 0x100 + b;
			string[j * c[0].size.x + i] = color;
			string[j * c[0].size.x + i + 1] = color;
			string[(j + 1) * c[0].size.x + i] = color;
			string[(j + 1) * c[0].size.x + i + 1] = color;
			if ((m_id[0] == ((int)i) && m_id[1] == ((int)j))
			|| (m_id[0] + 1 == ((int)i) && m_id[1] == ((int)j))
			|| (m_id[0] == ((int)i) && m_id[1] + 1== ((int)j))
			|| (m_id[0] + 1 == ((int)i) && m_id[1] + 1 == ((int)j)))
					*obj_id = id;
		}
	}
}
