/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bc_increase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:47:15 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/12 15:46:41 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_button	g_button = {
	.button_default = (char*)g_bplus_dflt,
	.button_fly = (char*)g_bplus_fly,
	.button_press = (char*)g_bplus_click,
	.size_x = BUTTON_DFLT_X,
	.size_y = BUTTON_DFLT_Y
};

int		bc_increase(void)
{
	static int	id;

	if (!id)
	{
		if ((id = mmlx_buttontype_create(-1, (t_button*)(&g_button))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
