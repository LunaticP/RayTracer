/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:29:40 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/21 20:29:42 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*temp1;
	unsigned char			*temp2;
	size_t					i;

	i = 0;
	temp1 = (unsigned char *)src;
	temp2 = (unsigned char *)dst;
	while (i < n)
	{
		temp2[i] = temp1[i];
		if (temp2[i] == (unsigned char)c)
			return ((void *)&(temp2[i + 1]));
		i++;
	}
	return (NULL);
}
