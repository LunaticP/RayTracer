/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:10:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/08 22:00:10 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libft.h>
# include <libocl.h>
# include <stdlib.h>
# include <pthread.h>

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
	cl_float4		pos;
	cl_float4		dir;
	float			tet;
	float			phi;
	float			rot;
	cl_float4		min;
	cl_float4		max;
	cl_int			col;
	cl_float		diff;
	cl_float		refl;
	cl_float		trans;
	cl_float		refr;
	t_type			type;
	cl_float		r;
	cl_float		su;
	cl_float		sd;
	cl_float		alpha;
	cl_char			caps;
	cl_float4		p1;
	cl_float4		p2;
	cl_float4		p3;
	short			tex;
	short			n_m;
	short			r_m;
}					t_obj;

typedef struct		s_cam
{
	cl_float4		ori;
	cl_float4		dirx;
	cl_float4		diry;
	cl_float4		dirz;
	cl_int2			size;
	cl_float4		viewplane;
	cl_float4		p;
	cl_float2		chunk;
	short			fast;
}					t_cam;

typedef struct		s_scene
{
	int				n_o;
	int				n_l;
	t_cam			cam;
	t_obj			*obj;
	t_obj			*light;
}					t_scene;

typedef struct		s_data
{
	int		size;
	int		n_t;
	int		n_o;
	int		n_l;
	int		width;
	int		height;
	int		scale;
	int		line;
	int		*tex;
	t_cam	cam;
	t_obj	*obj;
	t_obj	*light;
	unsigned char	*img;
}					t_data;

t_ocl_prog	*save_prog(int status, t_ocl_prog *prog);

#endif
