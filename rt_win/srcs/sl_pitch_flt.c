/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_pitch_flt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:24:57 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 18:24:07 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		sl_pitch_flt(t_mlx *win, t_pos *pos, t_fslider *sldr, int *id)
{
	t_sliderlink	link;

	link.f_slider = sm_default_flt;
	link.data_sm = sldr;
	link.data_len = sizeof(t_fslider);
	link.pos_x = pos->x;
	link.pos_y = pos->y;
	link.cursor_pos_x = 0;
	link.cursor_pos_y = 0;
	if ((link.id = sc_pitch()) < 0 || 
									(*id = mmlx_slider_link(win, &link)) < 0)
		return (rt_win_error(__func__, RT_WIN_SLIDER_FLT));
	return (0);
}
