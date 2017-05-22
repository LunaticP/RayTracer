/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:55:22 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:55:23 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *out;
	char *tmp;

	if ((out = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
	{
		tmp = out;
		while (*s)
		{
			*tmp = f(*s);
			tmp++;
			s++;
		}
		*tmp = '\0';
		return (out);
	}
	return (NULL);
}
