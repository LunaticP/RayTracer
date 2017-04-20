/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:55:54 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:55:55 by pgourran         ###   ########.fr       */
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
