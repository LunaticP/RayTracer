/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp_decrease_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:42:43 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 20:17:12 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bp_decrease_f(int id, int keycode, void *dta)
{
	t_fbutton		*data;

	data = (t_fbutton*)dta;
	if (keycode == 1)
	{
		if (*data->value - *data->pitch >= FTOA_MAX_VALUE)
			*data->value = FTOA_MAX_VALUE;
		else if (*data->value - *data->pitch <= FTOA_MIN_VALUE)
			*data->value = FTOA_MIN_VALUE;
		else
			*data->value -= *data->pitch;
	}
	return (id);
}
