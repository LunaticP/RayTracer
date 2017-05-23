/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_pitch_flt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:24:57 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_slider g_slider = {
	.cursor = (char *)g_cursor,
	.cursor_sizex = CURSOR_PITCH_X,
	.cursor_sizey = CURSOR_PITCH_Y,
	.slider = (char *)g_slider_grey,
	.slider_sizex = SLIDER_PITCH_X,
	.slider_sizey = SLIDER_PITCH_Y,
	.slidertype = ST_CURSOR_YCENTER | ST_CURSOR_INSIDE
};

static int	sc_pitch(void)
{
	static int	id;

	if (!id)
	{
		if ((id = mmlx_slidertype_create(-1, (t_slider*)(&g_slider))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}

int			sl_pitch_flt(t_mmlx *win, t_pos *pos, t_fslider *sldr, int *id)
{
	t_sliderlink	link;

	link.f_slider = sm_default_flt;
	link.data_sm = sldr;
	link.data_len = sizeof(t_fslider);
	link.pos_x = pos->x;
	link.pos_y = pos->y;
	link.cursor_pos_x = SLIDER_PITCH_X;
	link.cursor_pos_y = (SLIDER_PITCH_Y - CURSOR_PITCH_Y) / 2;
	if ((link.id = sc_pitch()) < 0 ||
									(*id = mmlx_slider_link(win, &link)) < 0)
		return (rt_win_error(__func__, RT_WIN_SLIDER_FLT));
	return (0);
}
