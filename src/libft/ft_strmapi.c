/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:55:28 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:55:30 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s1, char (*f)(unsigned int, char))
{
	int		i;
	char	*out;
	char	*tmp;

	i = 0;
	if ((out = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
	{
		tmp = out;
		while (*s1)
		{
			*tmp = f(i++, *s1++);
			tmp++;
		}
		*tmp = '\0';
		return (out);
	}
	return (NULL);
}
