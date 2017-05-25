/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 07:00:26 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/10 21:21:55 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

char	*str_get_value(void *data)
{
	cl_float	*number;

	number = (cl_float*)data;
	return (rt_win_ftoa(*number));
}
