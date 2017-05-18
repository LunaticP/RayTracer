/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bc_modify_pitch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:57:27 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/12 15:50:12 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_button	g_button = {
	.button_default = (char*)g_bpitch_dflt,
	.button_fly = (char*)g_bpitch_fly,
	.button_press = (char*)g_bpitch_click,
	.size_x = BUTTON_PITCH_X,
	.size_y = BUTTON_PITCH_Y
};

int		bc_modify_pitch(void)
{
	static int	id;

	if (!id)
	{
		if ((id = mmlx_buttontype_create(-1, (t_button*)(&g_button))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
