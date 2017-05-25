/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 04:15:50 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/22 12:39:07 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMLX_H
# define MMLX_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>

# include <Carbon/Carbon.h>

/*
** ------------------------ About Carbon.h ------------------------------
** - Included in order to use mac's default keycodes                    -
** - Here we use 2 enum from Events.h include inside Carbon.h           -
** ----------------------------------------------------------------------
** ------------------------ Extract from Events.h ------------------------------
** ----------------------------------------------------------------------
** - Discussion:                                                        -
** -  These constants are the virtual keycodes defined originally in    -
** -  Inside Mac Volume V, pg. V-191. They identify physical keys on a  -
** -  keyboard. Those constants with "ANSI" in the name are labeled     -
** -  according to the key position on an ANSI-standard US keyboard.    -
** -  For example, kVK_ANSI_A indicates the virtual keycode for the key -
** -  with the letter 'A' in the US keyboard layout. Other keyboard     -
** -  layouts may have the 'A' key label on a different physical key;   -
** -  in this case, pressing 'A' will generate a different virtual      -
** -  keycode.                                                          -
** ----------------------------------------------------------------------
**enum {
**  kVK_ANSI_A                    = 0x00,
**  kVK_ANSI_S                    = 0x01,
**  kVK_ANSI_D                    = 0x02,
**  kVK_ANSI_F                    = 0x03,
**  kVK_ANSI_H                    = 0x04,
**  kVK_ANSI_G                    = 0x05,
**  kVK_ANSI_Z                    = 0x06,
**  kVK_ANSI_X                    = 0x07,
**  kVK_ANSI_C                    = 0x08,
**  kVK_ANSI_V                    = 0x09,
**  kVK_ANSI_B                    = 0x0B,
**  kVK_ANSI_Q                    = 0x0C,
**  kVK_ANSI_W                    = 0x0D,
**  kVK_ANSI_E                    = 0x0E,
**  kVK_ANSI_R                    = 0x0F,
**  kVK_ANSI_Y                    = 0x10,
**  kVK_ANSI_T                    = 0x11,
**  kVK_ANSI_1                    = 0x12,
**  kVK_ANSI_2                    = 0x13,
**  kVK_ANSI_3                    = 0x14,
**  kVK_ANSI_4                    = 0x15,
**  kVK_ANSI_6                    = 0x16,
**  kVK_ANSI_5                    = 0x17,
**  kVK_ANSI_Equal                = 0x18,
**  kVK_ANSI_9                    = 0x19,
**  kVK_ANSI_7                    = 0x1A,
**  kVK_ANSI_Minus                = 0x1B,
**  kVK_ANSI_8                    = 0x1C,
**  kVK_ANSI_0                    = 0x1D,
**  kVK_ANSI_RightBracket         = 0x1E,
**  kVK_ANSI_O                    = 0x1F,
**  kVK_ANSI_U                    = 0x20,
**  kVK_ANSI_LeftBracket          = 0x21,
**  kVK_ANSI_I                    = 0x22,
**  kVK_ANSI_P                    = 0x23,
**  kVK_ANSI_L                    = 0x25,
**  kVK_ANSI_J                    = 0x26,
**  kVK_ANSI_Quote                = 0x27,
**  kVK_ANSI_K                    = 0x28,
**  kVK_ANSI_Semicolon            = 0x29,
**  kVK_ANSI_Backslash            = 0x2A,
**  kVK_ANSI_Comma                = 0x2B,
**  kVK_ANSI_Slash                = 0x2C,
**  kVK_ANSI_N                    = 0x2D,
**  kVK_ANSI_M                    = 0x2E,
**  kVK_ANSI_Period               = 0x2F,
**  kVK_ANSI_Grave                = 0x32,
**  kVK_ANSI_KeypadDecimal        = 0x41,
**  kVK_ANSI_KeypadMultiply       = 0x43,
**  kVK_ANSI_KeypadPlus           = 0x45,
**  kVK_ANSI_KeypadClear          = 0x47,
**  kVK_ANSI_KeypadDivide         = 0x4B,
**  kVK_ANSI_KeypadEnter          = 0x4C,
**  kVK_ANSI_KeypadMinus          = 0x4E,
**  kVK_ANSI_KeypadEquals         = 0x51,
**  kVK_ANSI_Keypad0              = 0x52,
**  kVK_ANSI_Keypad1              = 0x53,
**  kVK_ANSI_Keypad2              = 0x54,
**  kVK_ANSI_Keypad3              = 0x55,
**  kVK_ANSI_Keypad4              = 0x56,
**  kVK_ANSI_Keypad5              = 0x57,
**  kVK_ANSI_Keypad6              = 0x58,
**  kVK_ANSI_Keypad7              = 0x59,
**  kVK_ANSI_Keypad8              = 0x5B,
**  kVK_ANSI_Keypad9              = 0x5C
**};
**
** keycodes for keys that are independent of keyboard layout
**enum {
**  kVK_Return                    = 0x24,
**  kVK_Tab                       = 0x30,
**  kVK_Space                     = 0x31,
**  kVK_Delete                    = 0x33,
**  kVK_Escape                    = 0x35,
**  kVK_Command                   = 0x37,
**  kVK_Shift                     = 0x38,
**  kVK_CapsLock                  = 0x39,
**  kVK_Option                    = 0x3A,
**  kVK_Control                   = 0x3B,
**  kVK_RightShift                = 0x3C,
**  kVK_RightOption               = 0x3D,
**  kVK_RightControl              = 0x3E,
**  kVK_Function                  = 0x3F,
**  kVK_F17                       = 0x40,
**  kVK_VolumeUp                  = 0x48,
**  kVK_VolumeDown                = 0x49,
**  kVK_Mute                      = 0x4A,
**  kVK_F18                       = 0x4F,
**  kVK_F19                       = 0x50,
**  kVK_F20                       = 0x5A,
**  kVK_F5                        = 0x60,
**  kVK_F6                        = 0x61,
**  kVK_F7                        = 0x62,
**  kVK_F3                        = 0x63,
**  kVK_F8                        = 0x64,
**  kVK_F9                        = 0x65,
**  kVK_F11                       = 0x67,
**  kVK_F13                       = 0x69,
**  kVK_F16                       = 0x6A,
**  kVK_F14                       = 0x6B,
**  kVK_F10                       = 0x6D,
**  kVK_F12                       = 0x6F,
**  kVK_F15                       = 0x71,
**  kVK_Help                      = 0x72,
**  kVK_Home                      = 0x73,
**  kVK_PageUp                    = 0x74,
**  kVK_ForwardDelete             = 0x75,
**  kVK_F4                        = 0x76,
**  kVK_End                       = 0x77,
**  kVK_F2                        = 0x78,
**  kVK_PageDown                  = 0x79,
**  kVK_F1                        = 0x7A,
**  kVK_LeftArrow                 = 0x7B,
**  kVK_RightArrow                = 0x7C,
**  kVK_DownArrow                 = 0x7D,
**  kVK_UpArrow                   = 0x7E
** };
** -----------------------------------------------------------------------------
*/

/*
** -------------------------- Default Data --------------------------
** - Please Set the max value according to your machine             -
** ------------------------------------------------------------------
*/

# define DFLT_MAX_XWIN			2560
# define DFLT_MAX_YWIN			1440
# define DFLT_MIN_XWIN			1
# define DFLT_MIN_YWIN			1

# define DFLT_MAX_PARENT		10
# define DFLT_MAX_CHILD			10

# define DFLT_MAX_BUTTONTYPE	5
# define DFLT_MAX_SLIDERTYPE	6
# define DFLT_MAX_SWITCHTYPE	5

# define DFLT_MAX_BUTTONWIN		40
# define DFLT_MAX_STRINGWIN		60
# define DFLT_MAX_SLIDERWIN		10
# define DFLT_MAX_SWITCHWIN		10

/*
** ------------------------ Default Settings ------------------------
** - This part can be freely edited as long as it respects          -
** - the datamaxes above                                            -
** ------------------------------------------------------------------
*/

# define DFLT_XWIN			(DFLT_MAX_XWIN)
# define DFLT_YWIN			(DFLT_MAX_YWIN)
# define DFLT_XWIN_CHILD	200
# define DFLT_YWIN_CHILD	150
# define DFLT_PARENTNAME	"Parent"
# define DFLT_CHILDNAME		"Child"

/*
** ----------------------- Default KeyEvents ------------------------
** - This part links some events to keycodes, Feel free to edit them-
** ------------------------------------------------------------------
*/

# define L_CLICK				(1)
# define R_CLICK				(2)
# define SCROLL_UP				(4)
# define SCROLL_DOWN			(5)
# define DFLT_EXIT				kVK_Escape
# define SLIDER_MOUSE_KEYCODE	(1)

/*
** -------------------------- X11 Events ----------------------------
** - This part contains the defines concerning the events used      -
** - (taken from the X11 events)                                    -
** ------------------------------------------------------------------
*/

# define KEYPRESS		2
# define KEYRELEASE		3
# define BUTTONPRESS	4
# define BUTTONRELEASE	5
# define MOTIONNOTIFY	6
# define DESTROYNOTIFY	17

/*
** ------------------------ X11 Events Mask -------------------------
** - This part contains the defines concerning the masks of the     -
** - events used (taken from the X11 events)                        -
** ------------------------------------------------------------------
*/

# define KEYPRESSMASK			(1L << 0)
# define KEYRELEASEMASK			(1L << 1)
# define BUTTONPRESSMASK		(1L << 2)
# define BUTTONRELEASEMASK		(1L << 3)
# define POINTERMOTIONMASK		(1L << 6)
# define EXPOSUREMASK			(1L << 15)

/*
** -------------------------- Errors entry --------------------------
** - An enum associated with a char * [] in order to easily refer   -
** - and connect the id and the message of the errors               -
** ------------------------------------------------------------------
*/

int				mmlx_error(const char *prefix, int error);

enum			e_mmlx_error_array
{
	NO_ERROR,
	MALLOC_ERROR,
	NEW_WIN_ERROR,
	NEW_IMG_ERROR,
	NEW_PARENT_ERROR,
	NEW_CHILD_ERROR,
	MAX_PARENT_ERROR,
	MAX_CHILD_ERROR,
	MAX_BUTTONTYPE_ERROR,
	MAX_SLIDERTYPE_ERROR,
	MAX_SWITCHTYPE_ERROR,
	MAX_BUTTONWIN_ERROR,
	MAX_SLIDERWIN_ERROR,
	MAX_SWITCHWIN_ERROR,
	BAD_STATUS_BUTTON,
	BAD_STATUS_SWITCH,
	MISSED_IMG,
	LACK_DATA,
	DFLT_BUTTON_NOIMG,
	PRESS_BUTTON_NOIMG,
	FLY_BUTTON_NOIMG,
	SLIDER_NOIMG,
	CURSOR_NOIMG,
	BUTTON_WRONG_X,
	BUTTON_WRONG_Y,
	SLIDER_WRONG_X,
	SLIDER_WRONG_Y,
	CURSOR_WRONG_X,
	CURSOR_WRONG_Y,
	BUTTON_BAD_ID,
	SLIDER_BAD_ID,
	SWITCH_BAD_ID,
	BUTTON_BAD_FUNCTION,
	SLIDER_BAD_FUNCTION,
	SWITCH_BAD_FUNCTION,
	BUTTON_BAD_FUNC_DATA,
	SLIDER_BAD_FUNC_DATA,
	SWITCH_BAD_FUNC_DATA,
	BUTTON_BAD_XPOS,
	SLIDER_BAD_XPOS,
	CURSOR_BAD_XPOS,
	SWITCH_BAD_XPOS,
	BUTTON_BAD_YPOS,
	SLIDER_BAD_YPOS,
	CURSOR_BAD_YPOS,
	SWITCH_BAD_YPOS,
	BUTTON_NEGATIVE_ID,
	SLIDER_NEGATIVE_ID,
	STRING_NEGATIVE_ID,
	SWITCH_NEGATIVE_ID,
	BUTTON_UNUSED_ID,
	SLIDER_UNUSED_ID,
	STRING_UNUSED_ID,
	SWITCH_UNUSED_ID,
	WRONG_XSTART_STRING,
	WRONG_YSTART_STRING,
	LACK_OF_DATA_FOR_STRING,
	TOO_MANY_DATA_FOR_STRING,
	MAX_STRINGWIN_ERROR,
	SWITCH_ON_NOIMG,
	SWITCH_OFF_NOIMG,
	SWITCH_WRONG_X,
	SWITCH_WRONG_Y,
	UNEXPECTED_ERROR,
	ENUM_ERROR_SIZE
};

static const char *g_mmlx_error_array[ENUM_ERROR_SIZE] = {
	"",
	"Malloc failed",
	"New Window from mlx_new_window failed !",
	"New Image from mlx_new_image failed !",
	"New Parent from mmlx_get_parent failed !",
	"New Child can't be Malloc.",
	"No more Parent can be created, check the mmlx.h.",
	"No more Child can be created, check the mmlx.h.",
	"No more {Buttontype} can be created, check the mmlx.h.",
	"No more {Slidertype} can be created, check the mmlx.h.",
	"No more {Switchtype} can be created, check the mmlx.h.",
	"No more {Button} in this win can be created, check the mmlx.h.",
	"No more {Slider} in this win can be created, check the mmlx.h.",
	"No more {Switch} in this win can be created, check the mmlx.h.",
	"Internal error, the status of {button} is wrong, Don't touch to {t_mmlx}!",
	"Internal error, the status of {switch} is wrong, Don't touch to {t_mmlx}!",
	"It seems that the texture has evolved in NULL !",
	"Where is the data ? A NULL appear in the data.",
	"Where is the default button image ?",
	"where is the press button image.",
	"where is the fly button image.",
	"where is the slider image.",
	"where is the cursor image.",
	"looks like the {button} x size is not good.",
	"looks like the {button} y size is not good.",
	"looks like the {slider} x size is not good.",
	"looks like the {slider} y size is not good.",
	"looks like the {cursor} x size is not good.",
	"looks like the {cursor} y size is not good.",
	"looks like the ID of the {button} is wrong.",
	"looks like the ID of the {slider} is wrong.",
	"looks like the ID of the {switch} is wrong.",
	"looks like the function linked for the {button} is wrong.",
	"looks like the function linked for the {slider} is wrong.",
	"looks like the function linked for the {switch} is wrong.",
	"looks like the {data} linked for the function of the {button} is wrong.",
	"looks like the {data} linked for the function of the {slider} is wrong.",
	"looks like the {data} linked for the function of the {switch} is wrong.",
	"looks like the {xpos} make the {button} out of the window.",
	"looks like the {xpos} make the {slider} out of the window.",
	"looks like the {xpos} make the {cursor} out of the window.",
	"looks like the {xpos} make the {switch} out of the window.",
	"looks like the {ypos} make the {button} out of the window.",
	"looks like the {ypos} make the {slider} out of the window.",
	"looks like the {ypos} make the {cursor} out of the window.",
	"looks like the {ypos} make the {switch} out of the window.",
	"The ID is negative, all {button} are unlink!",
	"The ID is negative, all {slider} are unlink!",
	"The ID is negative, all {string} are remove!",
	"The ID is negative, all {switch} are remove!",
	"The ID of the {button} is unused, nothing to do!",
	"The ID of the {slider} is unused, nothing to do!",
	"The ID of the {string} is unused, nothing to do!",
	"The ID of the {switch} is unused, nothing to do!",
	"looks like the xpos of a string don't start in the window",
	"looks like the ypos of a string don't start in the window",
	"The function and the string are unavailable, please give one of them",
	"The function and the string are both available, please give just one",
	"No more Strings in this win can be created, check the mmlx.h.",
	"Where is the {switch_on} image, here set on (null)",
	"Where is the {switch_off} image, here set on (null)",
	"looks like the {switch.size_x} is not good",
	"looks like the {switch.size_y} is not good",
	"Unexpected error !"
};

/*
** ----------------------- Internal Defines -------------------------
** -                                                                -
** ------------------------------------------------------------------
*/

# define BUTTON_DEFAULT		(1 << 0)
# define BUTTON_FLYED		(1 << 1)
# define BUTTON_PRESSED		(1 << 2)
# define BUTTON_UNUSED		(1 << 3)

# define SLIDER_RELEASED	(0)
# define SLIDER_PRESSED		(1 << 0)

# define ST_CURSOR_NORULE		(0)
# define ST_CURSOR_INSIDE		(1 << 0)
# define ST_CURSOR_XFIXED		(1 << 1)
# define ST_CURSOR_YFIXED		(1 << 2)
# define ST_CURSOR_XCENTER		((1 << 3) | ST_CURSOR_XFIXED)
# define ST_CURSOR_YCENTER		((1 << 4) | ST_CURSOR_YFIXED)

# define SWITCH_UNUSED		(1 << 0)
# define SWITCH_ON			(1 << 1)
# define SWITCH_OFF			(1 << 2)

# define BG_BUTTON_COLOR	0xFF000000
# define BG_DFLT_COLOR		0x00000000

/*
** ---------------------- External Structures -----------------------
** - This part contains the structures that the user must provide   -
** - in order to properly parameterize his environment              -
** - int	t_mousepress(int keycode, int x, int y, void *data)     -
** - int	t_mousefollow(int x, int y, void *data)                 -
** - int	t_keypress(int keycode void *data)                      -
** - int	t_buttonpress(int id, int keycode, void *data)          -
** - int	t_switchpress(int id, int status, void *data)           -
** ------------------------------------------------------------------
*/

typedef int(*t_mousepress)(int, int, int, void *);
typedef int(*t_mousefollow)(int, int, void *);
typedef int(*t_keypress)(int, void *);
typedef int(*t_close)(void *);

typedef struct	s_datawin
{
	char			*name;
	t_close			f_close;
	void			*data_cl;
	t_close			f_loop;
	void			*data_lp;
	t_keypress		f_keypress;
	void			*data_kp;
	t_keypress		f_keyrelease;
	void			*data_kr;
	t_mousepress	f_mousepress;
	void			*data_mp;
	t_mousepress	f_mouserelease;
	void			*data_mr;
	t_mousefollow	f_followmouse;
	void			*data_fm;
	int				xwin;
	int				ywin;
}				t_datawin;

typedef int(*t_buttonpress)(int, int, void *);

typedef struct	s_button
{
	char			*button_default;
	char			*button_fly;
	char			*button_press;
	int				size_x;
	int				size_y;
}				t_button;

typedef struct	s_buttonlink
{
	t_buttonpress	f_bpress;
	void			*data_bp;
	size_t			data_len;
	int				id;
	int				pos_x;
	int				pos_y;
}				t_buttonlink;

typedef int(*t_switchpress)(int, int, void *);

typedef struct	s_switch
{
	char	*switch_on;
	char	*switch_off;
	int		size_x;
	int		size_y;
}				t_switch;

typedef struct	s_switchlink
{
	t_switchpress	f_spress;
	void			*data_sp;
	size_t			data_len;
	int				id;
	int				pos_x;
	int				pos_y;
	int				switch_status;
}				t_switchlink;

typedef struct	s_slider
{
	char		*slider;
	char		*cursor;
	int			slider_sizex;
	int			slider_sizey;
	int			cursor_sizex;
	int			cursor_sizey;
	int			slidertype;
}				t_slider;

typedef void(*t_slidermove)(float, float, void *);

typedef struct	s_sliderlink
{
	t_slidermove	f_slider;
	void			*data_sm;
	size_t			data_len;
	int				id;
	int				pos_x;
	int				pos_y;
	int				cursor_pos_x;
	int				cursor_pos_y;
}				t_sliderlink;

typedef char*(*t_createstring)(void *);

typedef struct	s_stringput
{
	t_createstring	f_string;
	void			*f_data;
	char			*string;
	int				color;
	int				xpos;
	int				ypos;
}				t_stringput;

/*
** ---------------------- Internal Structures -----------------------
** - This part contains the structures used by the mmlx             -
** - Please do not edit them manually, this can lead to unexpected  -
** - errors                                                         -
** - Some details about {s_mlx} :                                   -
** -                          -> {mlx}, {win}, {img} are native     -
** -   from mlx                                                     -
** -                          -> {data} is native too (using image) -
** -                          -> {name} of the window               -
** -                          -> {used} link to {child_used[i]} of  -
** - the parent, initialised to 1, set to 0 when the win is destroy -
** -                          -> {count} link to {child} of the     -
** - parent, it's the number of child, increase/decrease of 1 when  -
** - a child is create/destroy                                      -
** -                          -> {f_keypress}, {f_buttonpress} and  -
** - {f_followmouse} are the &functions the user want add           -
** -                          -> {data_kp}, {data_bp}, {data_fm} are-
** - the &data that the user give to his function                   -
** -                          -> {child_tab[i]} link to the child i -
** - previously Malloc                                              -
** -                          -> {child_used[i]} contains 1/0 if    -
** - {child_tab[i]} is used/unused                                  -
** -                          -> {id} is the id of the win, the {id}-
** - of the native parents are 0 <= {id} < DFLT_MAX_PARENT even if  -
** - they are destroy/create. for the child, the id aren't static   -
** -                          -> {child} is the number of child,    -
** - childs are count just for 1 lvl, the child of a child isn't add-
** -                          -> {xwin}, {ywin} is the size of the  -
** - win in pixels                                                  -
** -                          -> {bpp}, {sizeline}, {endian} are    -
** - native from mlx (bpp : byte per pixel)                         -
** ------------------------------------------------------------------
*/

typedef struct	s_clickon
{
	t_buttonpress	f_button;
	void			*data_bp;
	t_button		data;
	int				pos_x;
	int				pos_y;
	int				button_status;
}				t_clickon;

typedef struct	s_slideon
{
	t_slidermove	f_slider;
	void			*data_sm;
	t_slider		data;
	int				pos_x;
	int				pos_y;
	int				cursor_pos_x;
	int				cursor_pos_y;
	int				old_cursor_pos_x;
	int				old_cursor_pos_y;
	int				slider_status;
}				t_slideon;

typedef struct	s_switchon
{
	t_switchpress	f_switch;
	void			*data_sp;
	t_switch		data;
	int				pos_x;
	int				pos_y;
	int				switch_status;
}				t_switchon;

typedef struct	s_mmlx
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_button;
	char			*data;
	char			*data_button;
	char			*name;
	int				*used;
	int				*count;
	t_close			f_close;
	void			*data_cl;
	t_close			f_loop;
	void			*data_lp;
	t_keypress		f_keypress;
	void			*data_kp;
	t_keypress		f_keyrelease;
	void			*data_kr;
	t_mousepress	f_mousepress;
	void			*data_mp;
	t_mousepress	f_mouserelease;
	void			*data_mr;
	t_mousefollow	f_followmouse;
	void			*data_fm;
	t_clickon		button_tab[DFLT_MAX_BUTTONWIN];
	int				button_used[DFLT_MAX_BUTTONWIN];
	t_stringput		string_tab[DFLT_MAX_STRINGWIN];
	int				string_used[DFLT_MAX_STRINGWIN];
	t_slideon		slider_tab[DFLT_MAX_SLIDERWIN];
	int				slider_used[DFLT_MAX_SLIDERWIN];
	t_switchon		switch_tab[DFLT_MAX_SWITCHWIN];
	int				switch_used[DFLT_MAX_SWITCHWIN];
	struct s_mmlx	*child_tab[DFLT_MAX_CHILD];
	int				child_used[DFLT_MAX_CHILD];
	int				id;
	int				child;
	int				xwin;
	int				ywin;
	int				bpp;
	int				sizeline;
	int				endian;
}				t_mmlx;

/*
** ----------------------- Internal Function ------------------------
** -                                                                -
** ------------------------------------------------------------------
*/

/*
**	Functions from my libft
*/

void			*ml_memcpy(void *dst, const void *src, size_t n);
void			ml_memdel(void **ap);
void			*ml_memset(void *b, int c, size_t len);
void			ml_putstr_fd(char const *s, int fd);
void			ml_putendl_fd(char const *s, int fd);
char			*ml_strdup(const char *s1);
void			ml_strdel(char **as);

/*
**	Button features
*/

int				mmlx_onbutton(t_clickon *button, int x, int y);
void			mmlx_button_flyed(t_mmlx *mlx, int x, int y);
void			mmlx_button_pressed(t_mmlx *mlx, int x, int y, int keycode);
void			mmlx_button_released(t_mmlx *mlx, int x, int y);
int				mmlx_button_update(t_mmlx *mlx, int i);

/*
**	Switch features
*/

int				mmlx_onswitch(t_switchon *data, int x, int y);
void			mmlx_switch_pressed(t_mmlx *mlx, int x, int y);
int				mmlx_switch_update(t_mmlx *mlx, int i);

/*
**	String features
*/

void			mmlx_string_update(t_mmlx *mlx);

/*
**	Slider features
*/

int				mmlx_onslider(t_slideon *slider, int x, int y);

void			mmlx_slider_pressed(t_mmlx *mlx, int x, int y);
void			mmlx_slider_released(t_mmlx *mlx, int x, int y);
void			mmlx_slider_catched(t_mmlx *mlx, int x, int y);

void			mmlx_cursorpos_update(t_mmlx *mlx, t_slideon *slider,
														int pos_x, int pos_y);
int				mmlx_slider_update(t_mmlx *mlx, int i);

/*
**	Window Features
*/

int				mmlx_inside_data_button(t_mmlx *mlx, void *pixel);
int				mmlx_create_id(void);
int				mmlx_create_win(t_mmlx *mlx);
t_mmlx			*mmlx_get_parent(int id);
void			mmlx_init_tmlx(t_mmlx *x, t_datawin *data);
void			mmlx_data_fill(t_mmlx *mlx);
int				mmlx_refresh(t_mmlx *mlx);

/*
**	Hooked functions
*/

int				mmlx_close(t_mmlx *mlx);
int				mmlx_keypress(int keycode, t_mmlx *mlx);
int				mmlx_keyrelease(int keycode, t_mmlx *mlx);
int				mmlx_mouse_press(int keycode, int x, int y, t_mmlx *mlx);
int				mmlx_mouse_release(int keycode, int x, int y, t_mmlx *mlx);
int				mmlx_mouse_xy(int x, int y, t_mmlx *mlx);

/*
** ----------------------- External Function ------------------------
** -                                                                -
** ------------------------------------------------------------------
*/

t_mmlx			*mmlx_create_child(t_mmlx *parent, t_datawin *data);
t_mmlx			*mmlx_create_parent(void *mlx, t_datawin *data);

int				mmlx_buttontype_create(int id, t_button *data);
int				mmlx_slidertype_create(int id, t_slider *data);
int				mmlx_switchtype_create(int id, t_switch *data);
int				mmlx_string_create(t_mmlx *win, t_stringput *data);

int				mmlx_button_link(t_mmlx *win, t_buttonlink *data);
int				mmlx_slider_link(t_mmlx *win, t_sliderlink *data);
int				mmlx_switch_link(t_mmlx *win, t_switchlink *data);

int				mmlx_button_unlink(int id, t_mmlx *win);
int				mmlx_switch_unlink(int id, t_mmlx *win);
int				mmlx_slider_unlink(int id, t_mmlx *win);
int				mmlx_string_remove(int id, t_mmlx *win);

#endif
