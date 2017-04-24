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
	short			tex;
	short			n_m;
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
	float			t2;
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

/*float4			get_normale(float4 hit, __global t_obj *o,int id)
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
   }*/


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
	if (o[id].type == cone || o[id].type == cylindre)
	{
		out = abs((int)(polar.x * (float)tex[j + 1]) % tex[j + 1]) * tex[j] \
  			+ (int)(polar.y * tex[j] / M_PI) % tex[j] + j + 2;
	}
	return (out > tex[0] || out < 0 ? 0 : out);
}

int				diffuse(__global t_obj *o,float *t, __global t_obj *l, t_ray ray, int id, int in, __global int *tex)
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
	float4			coef;
	float4			angle;
	float4			temp;
	float4			ctsn;
	float4			itpl;
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
	if (o[id].pos.w > 0.5f)
		return (color);
	hit = ray.dir * *t + ray.ori;
	coef.x = 4.0;
	coef.y = 1.0;
	coef.z = 4.0;
	temp = normalize(o[id].dir);
	angle = temp * (float)(M_PI / 4.0);
	temp = hit - o[id].pos;
	ctsn = 0.0f;
	ctsn.y = temp.y * cos(angle.x) - temp.z * sin(angle.x);
	ctsn.z = temp.y * sin(angle.x) + temp.z * cos(angle.x);
//	temp = ctsn;
//	ctsn.x = temp.x * cos(angle.y) + temp.z * sin(angle.y);
//	ctsn.z = -temp.x * sin(angle.y) + temp.z * cos(angle.y);
//	temp = ctsn;
	ctsn.x = temp.x * cos(angle.z) - temp.y * sin(angle.z);
	ctsn.y = temp.x * sin(angle.z) + temp.y * cos(angle.z);
	ctsn = -ctsn;
	if(o[id].type == sphere)
	{
		normale = norm_sphere(o, hit, id);
		polar.x = (atan(ctsn.y / sqrt(-ctsn.z * -ctsn.z + ctsn.x * ctsn.x))) + M_PI_2_F;
		polar.y = (atan(ctsn.x / -ctsn.z)) + M_PI_2_F;
	}
	else if (o[id].type == cone)
	{
		normale = norm_cone(o, hit, id, ray);
		polar.x = ctsn.y;
		polar.y = (atan(ctsn.x / -ctsn.z)) + M_PI_2_F;
		if ((int)(polar.x * 2.0) % 2)
			color = 0xFFFFFF - color;
	}
	else if (o[id].type == cylindre)
	{
		normale = norm_cylindre(o, hit, id, ray);
		polar.x = ctsn.y;
		polar.y = (atan(ctsn.x / -ctsn.z)) + M_PI_2_F;
	}
	else if (o[id].type == plan)
		normale = o[id].dir;
	else
		return(color);
	if (o[id].pos.w > 0.5f)
		normale *= -1.0f;
	if (o[id].n_m)
	{
		color = tex[tex_num(o[id].n_m, o, id, tex, polar)];
		normale.x += (color & 0xFF0000 / 0x10000) / 128.0 - 1.0;
		normale.y += (color & 0xFF00 / 0x100) / 128.0 - 1.0;
		normale.z += (color & 0xFF) / 128.0 - 2.0;
	}
	if (o[id].tex)
		color = tex[tex_num(o[id].tex, o, id, tex, polar)];
	else
		color = o[id].col;
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
	ray.dir *= -1;
	mid = (normalize(ray.dir) + normalize(vlight)) / 2;
	spec = pow(dot(normalize(mid), normalize(normale)), 150);
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
						if ((rt_sphere(o, i, &ray2.t, &ray2)) != 0)
						{
							if (t->x == t->y)
							{
								if(t->x > ray2.t && t->y < ray2.t2)
									ret = -1;
								break;
							}
							else if (ray2.t <= t->x && ray2.t2 >= t->x && ray2.t2 <= t->y)
							{
								t->x = ray2.t;
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
					}
					break;
				case cone :
					{
					}
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

float			sq(float a)
{
	return (a * a);
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
		if (t.x < t.y && t.x > 0.01f && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if (t.y > 0.01f && (t.y < ray->t || ray->t <= 0))
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
		if (t.x < t.y && t.x > 0.01 && (t.x < ray->t || ray->t <= 0))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if (t.y > 0.01 && (t.y < ray->t || ray->t <= 0))
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
		if (t.x < t.y && t.x > 0.001 && (t.x < ray->t || ray->t <= 0.001))
		{
			ray->t = t.x;
			ray->t2 = t.y;
			return (1);
		}
		else if (t.y > 0.001 && (t.y < ray->t || ray->t <= 0.001))
		{
			ray->t = t.y;
			ray->t2 = t.x;
			return (-1);
		}
	}
	return (0);
}


int				ray_match(__global t_obj *o, t_ray *ray)
{
	int		i;
	int		i2;
	int		ret;

	i = -1;
	i2 = -1;
	ray->t = 0;
	ret = -1;
	while (o[++i].type != end)
	{
		if (o[i].pos.w < 0.5f && o[i].dir.w < 0.5f)
		{
			switch (o[i].type)
			{
				case sphere :
					{
						if ((rt_sphere(o, i, &i2, ray)) != 0)
							ret = (i2 > 0) ? i2 - 1 : i;
					}
					break;
				case plan :
					{
						if ((rt_plan(o, i, ray)) != 0)
							ret = i;
					}
					break;
				case cylindre :
					{
						if ((rt_cylindre(o, i, &i2, ray)) != 0)
							ret = (i2 > 0) ? i2 - 1 : i;
					}
					break;
				case cone :
					{
						if ((rt_cone(o, i, &i2, ray)) != 0)
							ret = (i2 > 0) ? i2 - 1 : i;
					}
					break;
			}
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
	int pixel;
	int color;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	if (i < c[0].size.x && j < c[0].size.y)
	{
		string[j * c[0].size.x + i] = 0;
		c[0].ori;
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
				color = diffuse(o, &ray.t, l, ray, id, lt, tex);
				r = r + (color & 0xFF0000) / 0x10000 > 255 ? 255 : r + (color & 0xFF0000) / 0x10000;
				g = g + (color & 0xFF00) / 0x100 > 255 ? 255 : g + (color & 0xFF00) / 0x100;
				b = b + (color & 0xFF) > 255 ? 255 : b + (color & 0xFF);
			}
			color = r * 0x10000 + g * 0x100 + b;
			string[j * c[0].size.x + i] = color;
		}
	}
}
