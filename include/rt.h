/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:52:20 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/22 20:45:24 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define USAGE		"./rtv1 file\n"
# define DEBUG		0
# define DSR		1
# define W			1280
# define H			720
# define STEREO		0
# define OUT_FILE	1
# define WIDTH		(W * (DSR > 1 ? DSR : 1))
# define HEIGHT		(H * (DSR > 1 ? DSR : 1))
# define _

# include <libft.h>
# include <libocl.h>
# include <matrix.h>
# include <stdlib.h>
# include <float.h>
# include <math.h>
# include <key.h>
# include <obj.h>
# include <time.h>
# include <rt_win.h>

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
	cl_float4		rot;
	cl_int2			size;
	cl_float4		viewplane;
	cl_float4		p;
	cl_float2		chunk;
	short			fast;
	short			dsr;
	cl_int			ambient;
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
	int				tab_size[5];
	int				mouse[2];
	int				oid;
	t_mmlx			*parent;
}					t_mlx;

cl_float4			cl_cross(cl_float4 v1, cl_float4 v2);
cl_float4			normalize(cl_float4 v1);
cl_float			cl_dot(cl_float4 v1, cl_float4 v2);
void				trans_cam(t_cam *cam, cl_float4 axis, float dir);
void				rot_cam(t_cam *cam, cl_float4 axis, float angle);
void				img_file(unsigned char *img, t_mlx *mlx);
void				dsr(t_mlx *mlx);
void				print_log(char *str);
void				print_warning(char *str);
void				print_error(char *str);
void				print_info(char *str);
void				k_apply(int key, t_scene *s);
void				exit_error(char *str);
int					k_rel(int key, void *param);
int					k_press(int key, void *param);
int					m_press(int keycode, int x, int y, void *param);
int					ray_loop(void *param);
int					*get_texture(char **file);
int					*perlin(void);
int					*langton(void);
int					*get_texture(char **files);

#endif
