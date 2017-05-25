/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp_increase_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:39:01 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 21:11:59 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bp_increase_f(int id, int keycode, void *dta)
{
	t_fbutton		*data;

	data = (t_fbutton*)dta;
	if (keycode == 1)
	{
		if (*data->value + *data->pitch >= FTOA_MAX_VALUE)
			*data->value = FTOA_MAX_VALUE;
		else if (*data->value + *data->pitch <= FTOA_MIN_VALUE)
			*data->value = FTOA_MIN_VALUE;
		else
			*data->value += *data->pitch;
	}
	rt_win_redraw(NULL);
	return (id);
}
