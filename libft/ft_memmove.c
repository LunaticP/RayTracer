/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:34:24 by jogarcia          #+#    #+#             */
/*   Updated: 2016/01/07 00:17:16 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*new;
	unsigned char		*old;

	old = (unsigned char *)src;
	new = (unsigned char *)dst;
	if ((new < old) && (len))
		ft_memcpy(new, old, len);
	else if ((new > old) && (len))
	{
		len--;
		while (len)
		{
			new[len] = old[len];
			len--;
		}
		new[len] = old[len];
	}
	return (dst);
}
