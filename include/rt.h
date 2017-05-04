/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:10:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/04 10:57:32 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define USAGE "./rtv1 file\n"
# define DSR	2
# define W		1280
# define H		720
# define WIDTH	W * (DSR > 1 ? DSR : 1)
# define HEIGHT	H * (DSR > 1 ? DSR : 1)

# include <libft.h>
# include <libocl.h>
# include <matrix.h>
# include <mlx.h>
# include <stdlib.h>
# include <float.h>
# include <math.h>
# include <key.h>
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
	short			dsr;
}					t_cam;

typedef struct		s_scene
{
	t_cam			cam;
	t_obj			*obj;
	t_obj			*light;
}					t_scene;

typedef struct		s_mlx
{
	unsigned char	*p;
	void			*mlx;
	void			*win;
	void			*img;
	void			*tmp;
	void			*tmp2;
	char			*atmp;
	char			*atmp2;
	int				*tex;
	int				endian;
	int				key;
	int				bp;
	int				sl;
	t_scene			s;
	t_ocl_prog		prog;
}					t_mlx;

void	k_press(int key, int *k);
int		k_rel(int key, void *param);
void	k_apply(int key, t_scene *s);
int		*get_texture(char **file);

#endif
