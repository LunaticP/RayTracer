/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:55:37 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:55:39 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char *tmp;

	tmp = dst;
	while (*dst != '\0')
		dst++;
	while (*src && n)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
	*dst = '\0';
	return (tmp);
}
