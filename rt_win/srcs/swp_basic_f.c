/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swp_basic_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 01:54:44 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 21:12:41 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		swp_basic_f(int id, int status, void *dta)
{
	t_fswitch		*data;

	data = (t_fswitch*)dta;
	if (status)
		*data->value = data->on;
	else
		*data->value = data->off;
	rt_win_redraw(NULL);
	return (id);
}
