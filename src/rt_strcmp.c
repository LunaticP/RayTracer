/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:32:45 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:32:47 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			rt_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1)
		return (-1);
	return (0);
}
