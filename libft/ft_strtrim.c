/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:56:54 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:56:56 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lentrim(char const *s)
{
	size_t	len;

	len = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	while (*s)
	{
		len++;
		s++;
	}
	s--;
	if (len > 0)
	{
		while (*s == ' ' || *s == '\n' || *s == '\t')
		{
			len--;
			s--;
		}
	}
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*out;
	char	*tmp;
	size_t	len_out;

	len_out = lentrim(s) + 1;
	if ((out = (char *)malloc(sizeof(char) * len_out)))
	{
		tmp = out;
		while (*s == ' ' || *s == '\n' || *s == '\t')
			s++;
		while (len_out > 1)
		{
			*tmp = *s;
			tmp++;
			s++;
			len_out--;
		}
		*tmp = '\0';
		return (out);
	}
	return (NULL);
}
