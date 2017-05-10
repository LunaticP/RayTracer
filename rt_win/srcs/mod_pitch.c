/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_pitch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:39:30 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 19:16:33 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt_win.h"

static int	mod_pitch_slider(int posx, int posy, float *pitch, t_mlx *win)
{
	t_fslider	slider;
	t_pos		pos;
	int			id;
	t_fslider	*data;

	id = -1;
	slider = (t_fslider){.value = pitch, .min = 0.0, .max = 1.0};
	pos = (t_pos){.x = posx, .y = posy + 20};
	if (rt_win_error(__func__, sl_pitch_flt(win, &pos, &slider, &id)))
		return (-1);
	if (id >= 0 && id < DFLT_MAX_SLIDERWIN)
	{
		data = (t_fslider*)(win->slider_tab[id].data_sm);
		pos = (t_pos){.x = posx + 130, .y = posy};
		if (rt_win_error(__func__, bl_modify_pitch(win, data, pos.x, pos.y)))
			return (-1);
	}
	return (0);
}

static int	mod_pitch_string(int posx, int posy, float *pitch, t_mlx *win)
{
	t_stringput	string;

	string = (t_stringput){.color = STRING_COLOR,
		.f_string = NULL, .f_data = NULL, .string = "Pitch :",
		.xpos = posx, .ypos = posy};
	if (mmlx_string_create(win, &string) < 0)
		return (rt_win_error(__func__, MMLX_ERROR));
	string = (t_stringput){.color = STRING_COLOR,
		.f_string = str_get_value, .f_data = (void*)pitch,
		.string = NULL, .xpos = posx + 70, .ypos = posy};
	if (mmlx_string_create(win, &string) < 0)
		return (rt_win_error(__func__, MMLX_ERROR));
	return (0);
}

int			mod_pitch(int posx, int posy, float *pitch, t_mlx *win)
{
	if (rt_win_error(__func__, mod_pitch_string(posx, posy, pitch, win)))
		return (-1);
	if (rt_win_error(__func__, mod_pitch_slider(posx, posy, pitch, win)))
		return (-1);
	return (0);
}
