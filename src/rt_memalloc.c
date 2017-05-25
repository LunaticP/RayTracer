/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:30:05 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:30:10 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			*rt_memalloc(size_t size)
{
	void		*ptr;
	char		*tmp;

	ptr = malloc(size);
	if (ptr == NULL)
		exit(-1);
	tmp = (char *)ptr;
	while (size >= 8)
	{
		*(long int *)tmp = 0;
		tmp += 8;
		size -= 8;
	}
	while (size)
	{
		*tmp = 0;
		++tmp;
		--size;
	}
	return (ptr);
}
