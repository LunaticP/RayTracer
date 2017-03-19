/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:54:31 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:54:34 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *out;
	char *tmp;

	if (!(out = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1))))
		return (NULL);
	tmp = out;
	while (*s1)
	{
		*out = *s1;
		out++;
		s1++;
	}
	*out = '\0';
	return (tmp);
}
