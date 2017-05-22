/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_default_flt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:47:26 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		sl_default_flt(t_mmlx *win, t_pos *pos, t_fslider *sldr)
{
	t_sliderlink	link;

	link.f_slider = sm_default_flt;
	link.data_sm = sldr;
	link.data_len = sizeof(t_fslider);
	link.pos_x = pos->x;
	link.pos_y = pos->y;
	link.cursor_pos_x = 0;
	link.cursor_pos_y = 0;
	if ((link.id = sc_default()) < 0 || mmlx_slider_link(win, &link) < 0)
		return (rt_win_error(__func__, RT_WIN_SLIDER_FLT));
	return (0);
}
