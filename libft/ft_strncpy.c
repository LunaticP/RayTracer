/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:55:54 by jogarcia          #+#    #+#             */
/*   Updated: 2015/11/30 21:55:55 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*tmp;

	tmp = dst;
	while (*src && n)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
	while (n != 0)
	{
		*dst = '\0';
		dst++;
		n--;
	}
	return (tmp);
}
