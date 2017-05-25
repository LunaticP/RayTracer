/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:16:53 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:12:52 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_WIN_H
# define RT_WIN_H

# include "mmlx.h"
# include "button.h"
# include "slider.h"
# include "switch.h"
# include "obj.h"
# include "libft.h"

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

# define WIN_XLEN_EDIT		(350)
# define WIN_YLEN_EDIT		(1200)

# define FTOA_MAX_VALUE		(2000000000)
# define FTOA_MIN_VALUE		(-2000000000)
# define FTOA_NUM_FLOAT		(4)
# define FTOA_SEPARATOR		","
# define FTOA_SIZE_X		(160)

# define BG_PLAN			"./img/plan.xpm"
# define BG_SPHERE			"./img/sphere.xpm"
# define BG_CYLINDER		"./img/cylinder.xpm"
# define BG_CONE			"./img/cone.xpm"

/*
** -------------------- Color Button Settings -----------------------
** -                                                                -
** ------------------------------------------------------------------
*/

# define ALPHA		0xFF000000
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF

/*
** ------------------- Button Settings/Utilities --------------------
** -                                                                -
** ------------------------------------------------------------------
*/

# define NRM_MAX_DX		(MAX(MAX(CURSOR_DFLT_X, SLIDER_DFLT_X), BUTTON_DFLT_X))
# define MAX_DFLT_X		(MAX(NRM_MAX_DX, SWITCH_DFLT_X))
# define NRM_MAX_DY		(MAX(MAX(CURSOR_DFLT_Y, SLIDER_DFLT_Y), BUTTON_DFLT_Y))
# define MAX_DFLT_Y		(MAX(NRM_MAX_DY, SWITCH_DFLT_Y))

# define MAX_COLOR_X	(MAX(CURSOR_COLOR_X, SLIDER_COLOR_X))
# define MAX_COLOR_Y	(MAX(CURSOR_COLOR_Y, SLIDER_COLOR_Y))

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

typedef struct	s_fswitch
{
	cl_float	*value;
	uint64_t	offset;
	float		on;
	float		off;
}				t_fswitch;

typedef struct	s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct	s_cslider
{
	uint32_t	*color;
	t_pos		pos;
	t_mmlx		*win;
}				t_cslider;

int				rt_fkeypress(int keypress, void *data);
int				rt_fclose(void *data);
int				rt_win_getpitch(int i, float **pitch);
void			rt_win_redraw(int *key);

int				bc_modify_pitch(void);
int				sl_pitch_flt(t_mmlx *win, t_pos *pos, t_fslider *sldr, int *id);
int				bl_modify_pitch(t_mmlx *win, t_fslider *slider, int x, int y);
int				bp_modify_pitch(int id, int keycode, void *data);
int				mod_pitch(int posx, int posy, float *pitch, t_mmlx *win);

int				sl_color_int(t_mmlx *win, t_pos *pos, t_cslider *data,
																	int color);
int				mod_color(int posx, int posy, int *color, t_mmlx *win);
void			mod_color_block(int posx, int posy, uint32_t color,
																t_mmlx *win);
void			sm_color_red(float ratiox, float ratioy, void *data);
void			sm_color_green(float ratiox, float ratioy, void *data);
void			sm_color_blue(float ratiox, float ratioy, void *data);

int				sc_default(void);
int				sl_default_flt(t_mmlx *win, t_pos *pos, t_fslider *sldr);
void			sm_default_flt(float ratiox, float ratioy, void *data);

int				swc_basic(void);
int				swl_basic_flt(t_mmlx *win, t_pos *pos, t_fswitch *data);
int				swp_basic_f(int id, int status, void *dta);

int				bc_decrease(void);
int				bc_increase(void);
int				bl_decr_flt(cl_float *value, t_mmlx *win, float *pitch,
																	t_pos *pos);
int				bl_incr_flt(cl_float *value, t_mmlx *win, float *pitch,
																	t_pos *pos);
int				bp_decrease_f(int id, int keycode, void *dta);
int				bp_increase_f(int id, int keycode, void *dta);

int				bl_settings_default(t_obj *obj, t_mmlx *win, float *pitch);
int				bl_settings_cone(t_obj *obj, t_mmlx *win, float *pitch);
int				bl_settings_cylinder(t_obj *obj, t_mmlx *win, float *pitch);
int				bl_settings_sphere(t_obj *obj, t_mmlx *win, float *pitch);

int				win_create_plan(t_mmlx *parent, t_obj *obj);
int				win_create_cone(t_mmlx *parent, t_obj *obj);
int				win_create_sphere(t_mmlx *parent, t_obj *obj);
int				win_create_cylinder(t_mmlx *parent, t_obj *obj);

char			*rt_win_ftoa(float number);
char			*str_get_value(void *data);
char			*str_get_color(void *data);
char			*str_get_switch(void *data);

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
	RT_WIN_SWITCH,
	RT_WIN_SLIDER_FLT,
	RT_NO_MORE_PITCH,
	RT_ENUM_ERROR_SIZE
};

static const char *g_rt_win_error_array[RT_ENUM_ERROR_SIZE] = {
	"",
	"Looks like MMLX send an error",
	"The button for decrease {float} from object isn't created",
	"The button for increase {float} from object isn't created",
	"The button for {switch} from object isn't created",
	"The slider {float} from object isn't created",
	"No more pitch available"
};

/*
** ------------------------ Button Settings -------------------------
** - This part contains some data who set the buttons               -
** ------------------------------------------------------------------
*/

# define NUM_DFLT_BUTTON		(12)
# define NUM_DFLT_SLIDER		(2)
# define NUM_DFLT_SWITCH		(4)
# define NUM_DFLT_PARAM	(NUM_DFLT_BUTTON + NUM_DFLT_SLIDER + NUM_DFLT_SWITCH)

# define NUM_SPHERE_BUTTON		(1)
# define NUM_SPHERE_PARAM		(NUM_SPHERE_BUTTON)

# define NUM_CYLINDER_BUTTON	(1)
# define NUM_CYLINDER_PARAM		(NUM_CYLINDER_BUTTON)

# define NUM_CONE_BUTTON		(1)
# define NUM_CONE_PARAM			(NUM_CONE_BUTTON)

# define XLEN_SEP				(BUTTON_DFLT_X + BUTTON_DFLT_X / 2)
# define XLEN_STR				(150)

# define YLEN_SEP				(MAX(MAX_DFLT_Y, 24) + 5)
# define YLEN_STR_SEP			(YLEN_SEP / 2)
# define YSIZE_STR				(20)

# define XPOS_STR_START			(WIN_XLEN_EDIT - XLEN_STR - MAX_DFLT_X - 10)
# define SLIDER_DIFF_X			((MAX_DFLT_X - SLIDER_DFLT_X) / 2)
# define BUTTON_DIFF_X			((MAX_DFLT_X - XLEN_SEP - BUTTON_DFLT_X) / 2)
# define SWITCH_DIFF_X			((MAX_DFLT_X - SWITCH_DFLT_X) / 2)
# define XPOS_SWITCH_START		(XPOS_STR_START + XLEN_STR)
# define XPOS_BUTTON_START		(XPOS_STR_START + XLEN_STR)
# define XPOS_SLIDER_START		(XPOS_BUTTON_START)

# define YPOS_SWITCH_START		(50)
# define YPOS_BUTTON_START		(YPOS_SWITCH_START + YLEN_SEP * NUM_DFLT_SWITCH)
# define YPOS_SLIDER_START		(YPOS_BUTTON_START + YLEN_SEP * NUM_DFLT_BUTTON)
# define YPOS_SPHERE_START		(YPOS_SLIDER_START + YLEN_SEP * NUM_DFLT_SLIDER)
# define YPOS_CYLINDER_START	(YPOS_SPHERE_START)
# define YPOS_CONE_START		(YPOS_SPHERE_START)
# define YPOS_STR_START			(YPOS_SWITCH_START)
# define SLIDER_DIFF_Y			((MAX_DFLT_Y - SLIDER_DFLT_Y) / 2)
# define BUTTON_DIFF_Y			((MAX_DFLT_Y - BUTTON_DFLT_Y) / 2)
# define SWITCH_DIFF_Y			((MAX_DFLT_Y - SWITCH_DFLT_Y) / 2)

# define STRING_COLOR			(0x00CCCCCC)

# define MOD_PITCH_SCALE	(10)
# define MOD_SL_START		(20)
# define NORM_1X		(BUTTON_PITCH_X + CURSOR_PITCH_X * 2 + SLIDER_PITCH_X)
# define MOD_PITCH_SIZE_X	(MAX(NORM_1X, BUTTON_PITCH_X + 60 + FTOA_SIZE_X))
# define NORM_1Y			(MAX(SLIDER_PITCH_Y, CURSOR_PITCH_Y) + MOD_SL_START)
# define MOD_PITCH_SIZE_Y	(MAX(BUTTON_PITCH_Y, NORM_1Y))
# define MOD_PITCH_X(xwin)	(xwin - MOD_PITCH_SIZE_X - 1)
# define MOD_PITCH_Y(ywin)	(ywin - MOD_PITCH_SIZE_Y - 1)
# define MOD_PITCH_XSTART	((WIN_XLEN_EDIT - MOD_PITCH_SIZE_X) / 2)
# define MOD_PITCH_YSTART	(MOD_PITCH_Y(WIN_YLEN_EDIT - 50))

# define MOD_COLOR_STRING	(4)
# define MOD_COLOR_SLIDER	(3)
# define MOD_COLOR_SPACE_X	(30)
# define MOD_COLOR_SPACE_Y	(5)
# define MOD_COLOR_SLSTRT	(7)
# define MOD_COLOR_STRING_X	(60)
# define MOD_COLOR_BLOCK_X	(150)
# define MOD_COLOR_BLOCK_Y	(20)
# define NORM_2		((MAX_COLOR_Y + MOD_COLOR_SPACE_Y) * MOD_COLOR_STRING)
# define MOD_COLOR_SIZE_Y	(NORM_2 + MOD_COLOR_SPACE_Y + MOD_COLOR_BLOCK_Y)
# define MOD_COLOR_SIZE_X	(MOD_COLOR_STRING_X + MAX_COLOR_X + CURSOR_COLOR_X)
# define MOD_COLOR_X(xwin)	(xwin - MOD_COLOR_SIZE_X)
# define MOD_COLOR_Y(ywin)	(ywin - MOD_COLOR_SIZE_Y)
# define MOD_COLOR_XSTART	((WIN_XLEN_EDIT - MOD_COLOR_SIZE_X) / 2)
# define MOD_COLOR_YSTART	(MOD_COLOR_Y(MOD_PITCH_YSTART))

# define F4_X		(0)
# define F4_Y		(1)
# define F4_Z		(2)
# define F4_W		(3)

# define OFFSETOF(type, member) ((uint64_t)&((type*)0)->member)

static const uint64_t		g_rt_offset_allobj[NUM_DFLT_PARAM] = {
	OFFSETOF(t_obj, min.s[F4_W]),
	OFFSETOF(t_obj, max.s[F4_W]),
	OFFSETOF(t_obj, pos.s[F4_W]),
	OFFSETOF(t_obj, trans),
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
	OFFSETOF(t_obj, refl)
};

static const uint64_t		g_rt_offset_button_sphere[NUM_SPHERE_BUTTON] = {
	OFFSETOF(t_obj, r)
};

static const uint64_t		g_rt_offset_button_cylinder[NUM_CYLINDER_BUTTON] = {
	OFFSETOF(t_obj, r)
};

static const uint64_t		g_rt_offset_button_cone[NUM_CONE_BUTTON] = {
	OFFSETOF(t_obj, alpha)
};

static const uint64_t		g_rt_offset_button_all_object[NUM_DFLT_BUTTON] = {
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
	OFFSETOF(t_obj, dir.s[F4_Z])
};

static const t_fslider		g_rt_slider_all_object[NUM_DFLT_SLIDER] = {
	{.offset = OFFSETOF(t_obj, diff), .min = 0.0, .max = 1.0},
	{.offset = OFFSETOF(t_obj, refl), .min = 0.0, .max = 1.0}
};

static const t_fswitch	g_rt_switch_all_object[NUM_DFLT_SWITCH] = {
	{.offset = OFFSETOF(t_obj, min.s[F4_W]), .on = 1.0, .off = 0.0},
	{.offset = OFFSETOF(t_obj, max.s[F4_W]), .on = 1.0, .off = 0.0},
	{.offset = OFFSETOF(t_obj, pos.s[F4_W]), .on = 1.0, .off = 0.0},
	{.offset = OFFSETOF(t_obj, trans), .on = 1.0, .off = 0.0}
};

static const t_stringput	g_rt_strname_allobj[NUM_DFLT_PARAM] = {
	{.color = STRING_COLOR, .f_string = NULL, .string = "Minimum"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Maximum"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Objet Negatif"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Transparence"},
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
	{.color = STRING_COLOR, .f_string = NULL, .string = "Reflection"}
};

static const t_stringput	g_rt_strname_sphere[NUM_SPHERE_PARAM] = {
	{.color = STRING_COLOR, .f_string = NULL, .string = "Rayon"}
};

static const t_stringput	g_rt_strname_cylinder[NUM_CYLINDER_PARAM] = {
	{.color = STRING_COLOR, .f_string = NULL, .string = "Rayon"}
};

static const t_stringput	g_rt_strname_cone[NUM_CONE_PARAM] = {
	{.color = STRING_COLOR, .f_string = NULL, .string = "Alpha"}
};

static const t_stringput	g_rt_strvalue_allobj[NUM_DFLT_PARAM] = {
	{.color = STRING_COLOR, .f_string = str_get_switch, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_switch, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_switch, .string = NULL},
	{.color = STRING_COLOR, .f_string = str_get_switch, .string = NULL},
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

static const t_stringput	g_rt_strvalue_sphere[NUM_SPHERE_PARAM] = {
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL}
};

static const t_stringput	g_rt_strvalue_cylinder[NUM_CYLINDER_PARAM] = {
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL}
};

static const t_stringput	g_rt_strvalue_cone[NUM_CONE_PARAM] = {
	{.color = STRING_COLOR, .f_string = str_get_value, .string = NULL}
};

static const t_stringput	g_mod_color[MOD_COLOR_STRING] = {
	{.color = RED, .f_string = NULL, .string = "Rouge"},
	{.color = GREEN, .f_string = NULL, .string = "Vert"},
	{.color = BLUE, .f_string = NULL, .string = "Bleu"},
	{.color = STRING_COLOR, .f_string = NULL, .string = "Couleur :"}
};

static const t_slidermove	g_function_color[MOD_COLOR_SLIDER] = {
	sm_color_red,
	sm_color_green,
	sm_color_blue
};

#endif
