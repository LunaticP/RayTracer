/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bc_decrease.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:09:35 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/12 15:48:49 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_button	g_button = {
	.button_default = (char*)g_bminus_dflt,
	.button_fly = (char*)g_bminus_fly,
	.button_press = (char*)g_bminus_click,
	.size_x = BUTTON_DFLT_X,
	.size_y = BUTTON_DFLT_Y
};

int		bc_decrease(void)
{
	static int	id;

	if (!id)
	{
		if ((id = mmlx_buttontype_create(-1, (t_button*)(&g_button))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
