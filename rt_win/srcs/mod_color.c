/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 20:42:00 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static int	mod_color_slider(int posx, int posy, int *color, t_mmlx *win)
{
	t_pos		pos;
	int			i;
	t_cslider	data_color;

	data_color = (t_cslider){.pos.x = posx, .pos.y = posy, .win = win,
												.color = (uint32_t*)color};
	i = 0;
	pos = (t_pos){.x = posx + MOD_COLOR_STRING_X, .y = posy + MOD_COLOR_SLSTRT};
	while (i < MOD_COLOR_SLIDER)
	{
		if (rt_win_error(__func__, sl_color_int(win, &pos, &data_color, i)))
			return (-1);
		pos.y += MAX_COLOR_Y + MOD_COLOR_SPACE_Y;
		i++;
	}
	return (0);
}

static int	mod_color_string(int posx, int posy, int *color, t_mmlx *win)
{
	t_stringput		data;
	int				i;

	i = 0;
	while (i < MOD_COLOR_STRING)
	{
		data = g_mod_color[i];
		data.xpos = posx + (i + 1 == MOD_COLOR_STRING ? MOD_COLOR_SPACE_X : 0);
		data.ypos = posy;
		if (mmlx_string_create(win, &data) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
		posy += MAX_COLOR_Y + MOD_COLOR_SPACE_Y;
		i++;
	}
	data.f_string = str_get_color;
	data.f_data = (void*)color;
	data.string = NULL;
	data.xpos += 90;
	if (mmlx_string_create(win, &data) < 0)
		return (rt_win_error(__func__, MMLX_ERROR));
	return (0);
}

int			mod_color(int posx, int posy, int *color, t_mmlx *win)
{
	if (rt_win_error(__func__, mod_color_string(posx, posy, color, win)))
		return (-1);
	if (rt_win_error(__func__, mod_color_slider(posx, posy, color, win)))
		return (-1);
	mod_color_block(posx, posy, *color, win);
	return (0);
}
