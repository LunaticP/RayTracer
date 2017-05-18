/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_decr_flt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 19:20:52 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bl_decr_flt(cl_float *value, t_mmlx *win, float *pitch, t_pos *pos)
{
	t_buttonlink	link;
	t_fbutton		button;

	button.value = value;
	button.pitch = pitch;
	link.f_bpress = &bp_decrease_f;
	link.data_bp = &button;
	link.data_len = sizeof(t_fbutton);
	link.pos_x = pos->x;
	link.pos_y = pos->y;
	if ((link.id = bc_decrease()) < 0 || mmlx_button_link(win, &link) < 0)
		return (rt_win_error(__func__, RT_WIN_DEC_FLT_BUTTON));
	return (0);
}
