/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:06:03 by pgourran          #+#    #+#             */
/*   Updated: 2016/01/05 22:08:10 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int out;
	int is_negative;

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
	return (out);
}
