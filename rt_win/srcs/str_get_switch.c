/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_get_switch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:41:11 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 18:49:10 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

char	*str_get_switch(void *data)
{
	cl_float	*number;

	number = (cl_float*)data;
	if (*number < 0.5)
		return (ft_strdup("Off"));
	return (ft_strdup("On"));
}
