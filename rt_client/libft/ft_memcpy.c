/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 20:15:05 by pgourran          #+#    #+#             */
/*   Updated: 2016/01/05 22:09:14 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;

	ptr_dst = (unsigned char *)dst;
	while (n)
	{
		*ptr_dst = *((unsigned char *)(src));
		ptr_dst++;
		src++;
		n--;
	}
	return (dst);
}
