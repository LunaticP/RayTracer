/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:36:04 by jogarcia          #+#    #+#             */
/*   Updated: 2015/11/30 21:36:21 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	char	*tmp;
	size_t	len_out;

	len_out = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((out = (char *)malloc(sizeof(out) * len_out)))
	{
		tmp = out;
		while (*s1)
		{
			*tmp = *s1;
			tmp++;
			s1++;
		}
		while (*s2)
		{
			*tmp = *s2;
			tmp++;
			s2++;
		}
		*tmp = '\0';
		return (out);
	}
	return (NULL);
}
