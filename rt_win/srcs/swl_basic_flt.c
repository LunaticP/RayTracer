/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swl_basic_flt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 01:34:32 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		swl_basic_flt(t_mmlx *win, t_pos *pos, t_fswitch *data)
{
	t_switchlink	link;

	link.f_spress = &swp_basic_f;
	link.data_sp = data;
	link.data_len = sizeof(t_fswitch);
	link.pos_x = pos->x;
	link.pos_y = pos->y;
	if (*data->value == data->on)
		link.switch_status = SWITCH_ON;
	else
	{
		link.switch_status = SWITCH_OFF;
		*data->value = data->off;
	}
	if ((link.id = swc_basic()) < 0 || mmlx_switch_link(win, &link) < 0)
		return (rt_win_error(__func__, RT_WIN_SWITCH));
	return (0);
}
