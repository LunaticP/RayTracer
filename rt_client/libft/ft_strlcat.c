/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:58:20 by pgourran          #+#    #+#             */
/*   Updated: 2015/11/30 21:47:00 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t buf_size)
{
	unsigned int i;
	unsigned int dst_len;
	unsigned int src_len;

	dst_len = ft_strlen(dst) + 1;
	src_len = ft_strlen(src);
	i = 0;
	if (buf_size > dst_len)
	{
		while (i < (buf_size - dst_len))
		{
			dst[dst_len - 1 + i] = src[i];
			i++;
		}
		dst[dst_len - 1 + i] = '\0';
	}
	if (buf_size >= dst_len)
		return (dst_len + src_len - 1);
	else
		return (src_len + buf_size);
}
