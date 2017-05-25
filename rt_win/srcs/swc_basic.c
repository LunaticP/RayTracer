/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swc_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 02:04:08 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 02:08:35 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_switch	g_switch = {
	.switch_on = (char*)g_switch_basic_on,
	.switch_off = (char*)g_switch_basic_off,
	.size_x = SWITCH_DFLT_X,
	.size_y = SWITCH_DFLT_Y
};

int		swc_basic(void)
{
	static int	id;

	if (!id)
	{
		if ((id = mmlx_switchtype_create(-1, (t_switch*)(&g_switch))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
