/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_color_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 21:54:58 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_slider g_slider[3] = {
	{.cursor = (char *)g_cursor,
		.cursor_sizex = CURSOR_COLOR_X,
		.cursor_sizey = CURSOR_COLOR_Y,
		.slider = (char *)g_slider_red,
		.slider_sizex = SLIDER_COLOR_X,
		.slider_sizey = SLIDER_COLOR_Y,
		.slidertype = ST_CURSOR_YCENTER | ST_CURSOR_INSIDE},
	{.cursor = (char *)g_cursor,
		.cursor_sizex = CURSOR_COLOR_X,
		.cursor_sizey = CURSOR_COLOR_Y,
		.slider = (char *)g_slider_green,
		.slider_sizex = SLIDER_COLOR_X,
		.slider_sizey = SLIDER_COLOR_Y,
		.slidertype = ST_CURSOR_YCENTER | ST_CURSOR_INSIDE},
	{.cursor = (char *)g_cursor,
		.cursor_sizex = CURSOR_COLOR_X,
		.cursor_sizey = CURSOR_COLOR_Y,
		.slider = (char *)g_slider_blue,
		.slider_sizex = SLIDER_COLOR_X,
		.slider_sizey = SLIDER_COLOR_Y,
		.slidertype = ST_CURSOR_YCENTER | ST_CURSOR_INSIDE}
};

static int	sc_color(int col)
{
	static int	id[3];

	if (!id[col])
	{
		if ((id[col] = mmlx_slidertype_create(-1,
											(t_slider*)(&g_slider[col]))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id[col]);
}

int			sl_color_int(t_mmlx *win, t_pos *pos, t_cslider *data, int color)
{
	t_sliderlink	link;

	link.f_slider = g_function_color[color];
	link.data_sm = data;
	link.data_len = sizeof(t_cslider);
	link.pos_x = pos->x;
	link.pos_y = pos->y;
	link.cursor_pos_x = 0;
	link.cursor_pos_y = 0;
	if (((link.id = sc_color(color)) < 0 || mmlx_slider_link(win, &link) < 0))
		return (rt_win_error(__func__, RT_WIN_SLIDER_FLT));
	return (0);
}
