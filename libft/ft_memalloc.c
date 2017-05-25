/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 20:14:20 by jogarcia          #+#    #+#             */
/*   Updated: 2015/11/30 21:13:43 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void			*out;
	unsigned char	*tmp;

	if ((out = malloc(size)))
	{
		tmp = (unsigned char *)out;
		while (size != 0)
		{
			*tmp = 0;
			tmp++;
			size--;
		}
		return (out);
	}
	return (NULL);
}
