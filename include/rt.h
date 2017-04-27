/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:10:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/04/27 06:24:55 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define USAGE "./rtv1 file\n"
# define HEIGHT 1200
# define WIDTH 1600

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

typedef struct 		s_obj
{
	cl_float4		pos;
	cl_float4		dir;
<<<<<<< HEAD
=======
	float			tet;
	float			phi;
	float			rot;
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
	cl_float4		min;
	cl_float4		max;
	cl_int			col;
	cl_float		diff;
	cl_float		refl;
<<<<<<< HEAD
=======
	cl_float		trans;
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
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
<<<<<<< HEAD
	short			tex;
	short			n_m;
=======
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
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
<<<<<<< HEAD
	unsigned char			*p;
	int				bp;
	int				sl;
	int				endian;
	int				key;
	int				*tex;
=======
	void			*tmp;
	char			*atmp;
	void			*tmp2;
	char			*atmp2;
	char			*p;
	int				bp;
	int				*tex;
	int				sl;
	int				endian;
	int				key;
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
	t_scene			s;
	t_ocl_prog		prog;
}					t_mlx;

void	k_press(int key, int *k);
int		k_rel(int key, void *param);
void	k_apply(int key, t_scene *s);
int		*get_texture(char **file);

#endif
