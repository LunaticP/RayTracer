/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 00:17:36 by gsimeon           #+#    #+#             */
/*   Updated: 2017/04/10 00:51:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	*ml_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		*((char *)dst + i) = *((const char *)src + i);
		i++;
	}
	return (dst);
}
