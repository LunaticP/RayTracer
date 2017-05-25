/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_pitch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:39:30 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 18:27:41 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static int	mod_pitch_slider(int posx, int posy, float *pitch, t_mmlx *win)
{
	t_fslider	slider;
	t_pos		pos;
	int			id;
	t_fslider	*data;

	id = -1;
	slider = (t_fslider){.value = pitch, .min = 0.0, .max = 1.0};
	pos.x = posx + BUTTON_PITCH_X + CURSOR_PITCH_X;
	pos.y = posy + MOD_SL_START;
	if (rt_win_error(__func__, sl_pitch_flt(win, &pos, &slider, &id)))
		return (-1);
	if (id >= 0 && id < DFLT_MAX_SLIDERWIN)
	{
		data = (t_fslider*)(win->slider_tab[id].data_sm);
		pos = (t_pos){.x = posx, .y = posy};
		if (rt_win_error(__func__, bl_modify_pitch(win, data, pos.x, pos.y)))
			return (-1);
	}
	return (0);
}

static int	mod_pitch_string(int posx, int posy, float *pitch, t_mmlx *win)
{
	t_stringput	string;

	string = (t_stringput){.color = STRING_COLOR,
		.f_string = NULL, .f_data = NULL, .string = "Pitch:",
		.xpos = posx + BUTTON_PITCH_X + 10, .ypos = posy};
	if (mmlx_string_create(win, &string) < 0)
		return (rt_win_error(__func__, MMLX_ERROR));
	string = (t_stringput){.color = STRING_COLOR,
		.f_string = str_get_value, .f_data = (void*)pitch,
		.string = NULL, .xpos = posx + BUTTON_PITCH_X + 70, .ypos = posy};
	if (mmlx_string_create(win, &string) < 0)
		return (rt_win_error(__func__, MMLX_ERROR));
	return (0);
}

int			mod_pitch(int posx, int posy, float *pitch, t_mmlx *win)
{
	if (rt_win_error(__func__, mod_pitch_string(posx, posy, pitch, win)))
		return (-1);
	if (rt_win_error(__func__, mod_pitch_slider(posx, posy, pitch, win)))
		return (-1);
	return (0);
}
