/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swp_basic_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 01:54:44 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 05:55:59 by gsimeon          ###   ########.fr       */
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
	return (id);
}
