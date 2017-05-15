/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:10:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/15 16:02:55 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define USAGE "./rtv1 file\n"
# define DSR	1
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
# include <obj.h>
# include <time.h>

typedef struct		s_ant
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	cl_int2			pos;
	cl_int2			dir;
}					t_ant;

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
	int				n_o;
	int				n_l;
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
	int				cluster;
	t_scene			s;
	t_ocl_prog		prog;
}					t_mlx;

int					k_rel(int key, void *param);
void				k_press(int key, int *k);
void				k_apply(int key, t_scene *s);
int					*get_texture(char **file);
int					*perlin(void);
int					*langton(void);
cl_float			cl_dot(cl_float4 v1, cl_float4 v2);
cl_float4			cl_cross(cl_float4 v1, cl_float4 v2);
cl_float4			normalize(cl_float4 v1);
void				trans_cam(t_cam *cam, cl_float4 axis, float dir);
void				rot_cam(t_cam *cam, cl_float4 axis, float angle);

#endif
