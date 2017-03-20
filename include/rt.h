/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:10:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/20 10:58:11 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define USAGE "./rtv1 file\n"
# define HEIGHT 1400
# define WIDTH 2000

# include <libft.h>
# include <libocl.h>
# include <matrix.h>
# include <mlx.h>
# include <stdlib.h>
# include <float.h>
# include <math.h>
# include <key.h>

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

typedef struct		s_triangle
{
	cl_float4		pos;
	cl_float4		ori;
	cl_float4		p1;
	cl_float4		p2;
	cl_float4		p3;
	cl_float4		vn1;
	cl_float4		vn2;
	cl_float4		vn3;
	cl_int			col;
}					t_triangle;

typedef struct 		s_obj
{
	cl_float4		pos;
	cl_float4		dir;
	cl_float4		min;
	cl_float4		max;
	cl_int			col;
	cl_float		diff;
	cl_float		refl;
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
}					t_obj;

typedef struct		s_cam
{
	cl_float4		ori;
	cl_float4		dirx;
	cl_float4		diry;
	cl_float4		dirz;
	cl_int2			size;
	cl_float2		viewplane;
	cl_float4		p;
}					t_cam;

typedef struct		s_scene
{
	t_cam			cam;
	t_obj			*obj;
	t_obj			*light;
}					t_scene;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*p;
	int				bp;
	int				sl;
	int				endian;
	t_scene			s;
	t_ocl_prog		prog;
}					t_mlx;

t_list		*get_obj(char *path);

#endif
