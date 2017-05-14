/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:10:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/09 03:19:27 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define USAGE "./rtv1 file\n"
# define HEIGHT 900
# define WIDTH 700
# define _

# include <libft.h>
# include <libocl.h>
# include <matrix.h>
# include <mlx.h>
# include <stdlib.h>
# include <float.h>
# include <math.h>
# include <key.h>

#define DEBUG 0

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
	cl_float4		pos; // ne pas W sur les PLAN
	cl_float4		dir;
	float			tet;
	float			phi;
	cl_float4		rot;
	cl_float4		min; // si pas de min, min float sur chaque
	cl_float4		max; // si pas de max, max float sur chaque
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
	cl_float4		mod_tex;
	cl_float4		mod_normal;
	cl_float4		mod_ref;
	cl_float4		mod_trans;
	short			tex;
	short			n_m;
	short			r_m;
	short			t_m;
}					t_obj;

/*
dirx y et z n'est plus parser mais remplie apres (pas moi) MAIS PARSER un "DIR" en float4
donc x y et z sont le vecteur et un w qui est la rotation
*/
typedef struct		s_cam
{
	cl_float4		ori;
	cl_float4		dirx;
	cl_float4		diry;
	cl_float4		dirz;
	cl_float4		rot;
	cl_int2			size; // no
	cl_float4		viewplane; // z et w
	cl_float4		p; //
	cl_float2		chunk; //
	short			fast; //
	short			dsr;
}					t_cam;
/* A voir si bien tout dans les settings */
typedef struct 		s_set
{
	int				width;
	int				height;
	int				max_reflect; // pas supp 50
	int				anti_allias; // theoriquement jamais supp a 4
	int				ambient;
	cl_float		stereo; // stereoscopie 0 ou 1
	char			*name;
}					t_set;
/**/

typedef struct		s_scene
{
	t_cam			cam;
	t_obj			*obj;
	t_obj			*light;
	t_set			*set;
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
	int				tab_size[5];
}					t_mlx;

void	k_press(int key, int *k);
int		k_rel(int key, void *param);
void	k_apply(int key, t_scene *s);
int		*get_texture(char **file);

/*---------------------------------------------------*/

#define PADDING(X, Y)	char padding ## X[Y]

typedef	enum		e_elem
{
	OBJECTS,
	LIGHTS,
	CAMERA,
	SETTINGS,
	TEXTURES,
	SIZE
}					t_elem;

typedef struct 		s_parser
{
	void				*content;
	t_elem				elem;
	struct s_parser		*next;
}					t_parser;

t_mlx			rt_get_parser(char *path, t_mlx mlx);
t_parser		*rt_parser_file(char *file);
char			*rt_get_file(char *path);
void			rt_free_after_parser(char *file, t_parser *parser);

t_parser		*rt_parser_objects(char	*file, t_parser *ptr_parser);
t_parser		*rt_parser_camera(char *file, t_parser *parser);
t_parser		*rt_parser_lights(char *file, t_parser *parser);
t_parser		*rt_parser_textures(char *file, t_parser *parser);
t_parser		*rt_parser_settings(char *file, t_parser *parser);
void			rt_get_object(t_obj *obj, char *file, int mask_type);

void			***rt_list_to_tab(t_parser *parser, int *tab_size);

char			*rt_goto_bracket_close(char *file);
char			*rt_goto_data_end(char *file);

char			*rt_get_str_float(char *file);
char			*rt_next_float(char *file);

void			*rt_atoi(char *str);
void			*rt_get_char(char *file);
void			*rt_get_short(char *file);
void			*rt_get_str(char *file);
void			*rt_get_color(char *file);
void			*rt_get_int2(char *file);
void			*rt_get_float(char *str);
void			*rt_get_float2(char *file);
void			*rt_get_float3(char *file);
void			*rt_get_float4(char *file);
void			*rt_get_float4_end(char *file);
void			*rt_get_float4_neg(char *file);

void			rt_check_value(void ***tab);

int				rt_strcmp(const char *s1, const char *s2);
void			*rt_memalloc(size_t size);
char			*rt_strjoin(char *s1, char *s2);
void			*rt_useless(char *useless);
void			parser_error(t_list *file, char *path);
void			exit_error(char *str);

void			rt_add_mask(int *mask_check, int index);
void			rt_check_all_data(int mask, int check);
void			rt_check_min_max(int *mask, t_obj *obj);

void			print_data_obj(t_obj *obj);
void			print_data_camera(t_cam *cam);
void			print_data_settings(t_set *set);
void			test_read_tab(void *** tab);

#endif
