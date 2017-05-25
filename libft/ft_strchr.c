/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:53:34 by jogarcia          #+#    #+#             */
/*   Updated: 2016/05/23 14:55:35 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *out;

	if (!s)
		return (NULL);
	out = (char *)s;
	while (*out)
	{
		if (*out == c)
			return (out);
		out++;
	}
	if (c == 0)
		return (out);
	return (NULL);
}
