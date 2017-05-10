/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_modify_pitch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:58:50 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 19:16:55 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bl_modify_pitch(t_mlx *win, t_fslider *slider, int x, int y)
{
	t_buttonlink	link;

	link.f_bpress = &bp_modify_pitch;
	link.data_bp = &slider;
	link.data_len = sizeof(t_fslider*);
	link.pos_x = x;
	link.pos_y = y;
	if ((link.id = bc_modify_pitch()) < 0 || mmlx_button_link(win, &link) < 0)
		return (rt_win_error(__func__, RT_WIN_DEC_FLT_BUTTON));
	return (0);
}
