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
	float2			viewplane;
	float4			p;
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

float4		norm_cyl(__global t_obj *o, float4 hit, int id)
{
	float4	ret;
	float4	norbert;

	ret = hit - o[id].pos;
	norbert = normalize(o[id].dir);
	ret = hit.y * norbert;
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

int				diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id)
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

	color = o[id].col;
	hit = ray.dir * *t + ray.ori;
	if(o[id].type == sphere)
		normale = norm_sphere(o, hit, id);
	else if (o[id].type == plan)
		normale = o[id].dir;
	else
		return(color);
	vlight = l[0].pos - hit;
	norme = sqrt(vlight.x * vlight.x + vlight.y * vlight.y + vlight.z * vlight.z);
	dp = dot(normalize(vlight), normalize(normale));
	float4 rp = dot(normalize(refl(ray.dir, normale)), vlight);

	r = (color & 0xFF0000) / 0x10000;
	g = (color & 0xFF00) / 0x100;
	b = (color & 0xFF);
	rl = (l[0].col & 0xFF0000) / 0x10000 / 255;
	gl = (l[0].col & 0xFF00) / 0x100 / 255;
	bl = (l[0].col & 0xFF) / 255;
	r = r * dp * (l[0].r / (norme * norme)) * rl > 255 ? 255 : r * dp * (l[0].r / (norme * norme)) * rl;
	g = g * dp * (l[0].r / (norme * norme)) * gl > 255 ? 255 : g * dp * (l[0].r / (norme * norme)) * gl;
	b = b * dp * (l[0].r / (norme * norme)) * bl > 255 ? 255 : b * dp * (l[0].r / (norme * norme)) * bl;
	ray.dir *= -1;
	float4 mid = (normalize(ray.dir) + normalize(vlight)) / 2;
	float spec = pow(dot(normalize(mid), normalize(normale)), 20);
	fla.x = ((l[0].col && 0xFF0000) / 0x10000) * spec;
	fla.y = ((l[0].col && 0xFF00) / 0x100) * spec;
	fla.z = (l[0].col && 0xFF) * spec;
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
	return (ret);
}

__kernel void	raytracer(__global int* string, __global t_cam *c, __global t_obj *o,
	__global t_obj *l)
{
	t_ray	ray;
	size_t	i = get_global_id(0);
	size_t	j = get_global_id(1);
	int		id;
	float4	nor;

	if (i < c[0].size.x && j < c[0].size.y)
	{
		ray.dir = ray_from_coord(i, j, c);
		ray.ori = c[0].ori;
		if ((id = ray_match(o, &ray)) != -1)
		{
			string[j * c[0].size.x + i] = diffuse(o, &ray.t, l, ray, id);
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
