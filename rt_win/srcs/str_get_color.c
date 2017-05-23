/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 22:51:00 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/11 03:01:22 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

char	*str_get_color(void *data)
{
	int		*number;

	number = (int*)data;
	return (pf_itoa((void*)(uint64_t)(*number), 'p', 0));
}
