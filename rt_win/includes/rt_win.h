/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:16:53 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/10 20:26:58 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_WIN_H
# define RT_WIN_H

# include "mmlx.h"
# include "libft.h"
# include "obj.h"

/*
** ------------------------ Default Settings ------------------------
** -                                                                -
** ------------------------------------------------------------------
*/

# define DFLT_MAX_PITCH		(DFLT_MAX_CHILD)

# define WIN_NAME_PLAN		"Edition de Plan"
# define WIN_NAME_CONE		"Edition de Cone"
# define WIN_NAME_SPHERE	"Edition de Sphere"
# define WIN_NAME_CYLINDER	"Edition de Cylindre"

# define WIN_XLEN_EDIT		(1000)

# define WIN_YLEN_PLAN		(1100)
# define WIN_YLEN_CONE		(1200)
# define WIN_YLEN_SPHERE	(1200)
# define WIN_YLEN_CYLINDER	(1200)

# define FTOA_MAX_VALUE		(2000000000)
# define FTOA_MIN_VALUE		(-2000000000)
# define FTOA_NUM_FLOAT		(4)
# define FTOA_SEPARATOR		","

/*
** ----------------------- Internal utilities -----------------------
** - This part contains some struct and functions used for create   -
** - and link buttons in windows                                    -
** - bc_  for button create                                         -
** - bl_  for button link                                           -
** - bp_  for button press                                          -
** - sc_  for slider create                                         -
** - sl_  for slider link                                           -
** - sm_  for slider move                                           -
** ------------------------------------------------------------------
*/

typedef struct	s_fbutton
{
	cl_float	*value;
	float		*pitch;
}				t_fbutton;

typedef struct	s_fslider
{
	cl_float	*value;
	uint64_t	offset;
	float		min;
	float		max;
}				t_fslider;

typedef struct	s_pos
{
	int		x;
	int		y;
}				t_pos;

int		sc_pitch(void);
int		bc_modify_pitch(void);
int		sl_pitch_flt(t_mlx *win, t_pos *pos, t_fslider *sldr, int *id);
int		bl_modify_pitch(t_mlx *win, t_fslider *slider, int x, int y);
int		bp_modify_pitch(int id, int keycode, void *data);
int		mod_pitch(int posx, int posy, float *pitch, t_mlx *win);
int		rt_win_getpitch(int i, float **pitch);
int		rt_win_unused_pitch(int keypress, void *data);

int		sc_default(void);
int		sl_default_flt(t_mlx *win, t_pos *pos, t_fslider *sldr);
void	sm_default_flt(float ratiox, float ratioy, void *data);

int		bc_decrease(void);
int		bc_increase(void);
int		bl_decr_flt(cl_float *value, t_mlx *win, float *pitch, t_pos *pos);
int		bl_incr_flt(cl_float *value, t_mlx *win, float *pitch, t_pos *pos);
int		bp_decrease_f(int id, int keycode, void *dta);
int		bp_increase_f(int id, int keycode, void *dta);


int		bl_settings_default(t_obj *obj, t_mlx *win, float *pitch);
int		bl_settings_cone(t_obj *obj, t_mlx *win, float *pitch);
int		bl_settings_cylinder(t_obj *obj, t_mlx *win, float *pitch);
int		bl_settings_sphere(t_obj *obj, t_mlx *win, float *pitch);

int		win_create_plan(t_mlx *parent, t_obj* obj);
int		win_create_cone(t_mlx *parent, t_obj* obj);
int		win_create_sphere(t_mlx *parent, t_obj* obj);
int		win_create_cylinder(t_mlx *parent, t_obj* obj);

char	*rt_win_ftoa(float number);
char	*str_get_value(void *data);

/*
** -------------------------- Errors entry --------------------------
** - An enum associated with a char * [] in order to easily refer   -
** - and connect the id and the message of the errors               -
** ------------------------------------------------------------------
*/

int				rt_win_error(const char *prefix, int error);

enum			e_rt_win_error_array
{
	RT_NO_ERROR,
	MMLX_ERROR,
	RT_WIN_DEC_FLT_BUTTON,
	RT_WIN_INC_FLT_BUTTON,
	RT_WIN_SLIDER_FLT,
	RT_NO_MORE_PITCH,
	RT_ENUM_ERROR_SIZE
};

static const char *g_rt_win_error_array[RT_ENUM_ERROR_SIZE] = {
	"",
	"Looks like MMLX send an error",
	"The button for decrease {float} from object isn't created",
	"The button for increase {float} from object isn't created",
	"The slider {float} from object isn't created",
	"No more pitch available"
};

/*
** ------------------------ Button Settings -------------------------
** - This part contains some data who set the buttons               -
** ------------------------------------------------------------------
*/

# include "button.h"

# define NUM_DFLT_BUTTON		(12)
# define NUM_DFLT_SLIDER		(4)
# define NUM_DFLT_PARAM			(NUM_DFLT_BUTTON + NUM_DFLT_SLIDER)

# define NUM_SPHERE_BUTTON		(1)
# define NUM_CYLINDER_BUTTON	(3)
# define NUM_CONE_BUTTON		(3)

# define XLEN_SEP				(BUTTON_DFLT_X + 5)
# define XLEN_STR				(150)

# define YLEN_SEP				(MAX(MAX_DFLT_Y, 24) + 5)
# define YLEN_STR_SEP			(YLEN_SEP / 2)

# define XPOS_STR_START			(WIN_XLEN_EDIT - XLEN_STR - MAX_DFLT_X - 10)
# define XPOS_BUTTON_START		(XPOS_STR_START + XLEN_STR)
# define XPOS_SLIDER_START		(XPOS_BUTTON_START)

# define YPOS_BUTTON_START		(150)
# define YPOS_STR_START			(YPOS_BUTTON_START)
# define YPOS_SLIDER_START		(YPOS_BUTTON_START + YLEN_SEP * NUM_DFLT_BUTTON)
# define SLIDER_DIFF_Y			((MAX_DFLT_Y - SLIDER_DFLT_Y) / 2)
# define BUTTON_DIFF_Y			((MAX_DFLT_Y - BUTTON_DFLT_Y) / 2)

# define STRING_COLOR			(0x00CCCCCC)

# define PITCH_SCALE			(10)

# define F4_X					(0)
# define F4_Y					(1)
# define F4_Z					(2)

# define OFFSETOF(type, member) ((uint64_t)&((type*)0)->member)

static const uint64_t	g_rt_offset_button_all_object[NUM_DFLT_PARAM] = {
	OFFSETOF(t_obj, min.s[F4_X]),
	OFFSETOF(t_obj, min.s[F4_Y]),
	OFFSETOF(t_obj, min.s[F4_Z]),
	OFFSETOF(t_obj, max.s[F4_X]),
	OFFSETOF(t_obj, max.s[F4_Y]),
	OFFSETOF(t_obj, max.s[F4_Z]),
	OFFSETOF(t_obj, pos.s[F4_X]),
	OFFSETOF(t_obj, pos.s[F4_Y]),
	OFFSETOF(t_obj, pos.s[F4_Z]),
	OFFSETOF(t_obj, dir.s[F4_X]),
	OFFSETOF(t_obj, dir.s[F4_Y]),
	OFFSETOF(t_obj, dir.s[F4_Z]),
	OFFSETOF(t_obj, diff),
	OFFSETOF(t_obj, refl),
	OFFSETOF(t_obj, refr),
	OFFSETOF(t_obj, trans)
};

static const uint64_t g_rt_offset_button_sphere[NUM_SPHERE_BUTTON] = {
	OFFSETOF(t_obj, r)
};

static const uint64_t g_rt_offset_button_cylinder[NUM_CYLINDER_BUTTON] = {
	OFFSETOF(t_obj, r),
	OFFSETOF(t_obj, su),
	OFFSETOF(t_obj, sd)
};

static const uint64_t g_rt_offset_button_cone[NUM_CONE_BUTTON] = {
	OFFSETOF(t_obj, su),
	OFFSETOF(t_obj, sd),
	OFFSETOF(t_obj, alpha)
};

static const t_fslider	g_rt_slider_minmax[NUM_DFLT_SLIDER] = {
	{.offset = OFFSETOF(t_obj, diff), .min = 0.0, .max = 1.0},
	{.offset = OFFSETOF(t_obj, refl), .min = 0.0, .max = 1.0},
	{.offset = OFFSETOF(t_obj, refr), .min = 0.0, .max = 1.0},
	{.offset = OFFSETOF(t_obj, trans), .min = 0.0, .max = 1.0}
};

static const t_stringput g_rt_strname_allobj[NUM_DFLT_PARAM] = {
	{.color = STRING_COLOR, .f_string = NULL, .string = "Minimum (x)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Minimum (y)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Minimum (z)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Maximum (x)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Maximum (y)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Maximum (z)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Position (x)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Position (y)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Position (z)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Direction (x)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Direction (y)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Direction (z)"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Diffuse"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Reflection"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Refraction"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Transparence"}
};

static const t_stringput g_rt_strvalue_allobj[NUM_DFLT_PARAM] = {
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL}
};

# define MOD_COLOR_STRING	(4)

static const t_stringput g_mod_color[MOD_COLOR_STRING] = {
	{.color = RED, .f_string = NULL, .string = "Rouge"},
	{.color = GREEN, .f_string = NULL, .string = "Vert"},
	{.color = BLUE, .f_string = NULL, .string = "Bleu"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Couleur :"}
};

#endif
