/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bc_increase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:47:15 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 14:23:14 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bc_increase(void)
{
	static int	id;
	t_button	data;

	if (!id)
	{
		data.button_default = (char*)g_button_default;
		data.button_fly = (char*)g_button_fly;
		data.button_press = (char*)g_button_press;
		data.size_x = BUTTON_DFLT_X;
		data.size_y = BUTTON_DFLT_Y;
		if ((id = mmlx_buttontype_create(-1, &data)) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
