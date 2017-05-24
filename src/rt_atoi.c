/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:23:03 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:23:04 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				*rt_atoi(char *str)
{
	static int		out;
	int				is_negative;

	out = 0;
	while (*str > '\0' && *str <= ' ')
		str++;
	is_negative = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		out *= 10;
		out += (*str - '0');
		str++;
	}
	if (is_negative)
		out = -out;
	if (*str != ';')
		exit_error("EXIT : [rt_atoi.c]");
	return ((void *)&out);
}
