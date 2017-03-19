/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:56:46 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:56:47 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *out;
	char *tmp;

	if ((out = (char *)malloc(sizeof(char) * len + 1)))
	{
		tmp = out;
		s = &s[start];
		while (len--)
		{
			*tmp = *s;
			tmp++;
			s++;
		}
		*tmp = '\0';
		return (out);
	}
	return (NULL);
}
