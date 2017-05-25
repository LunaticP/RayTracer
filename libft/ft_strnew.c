/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:56:09 by jogarcia          #+#    #+#             */
/*   Updated: 2016/05/23 15:03:51 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *out;
	char *pt_out;

	if (!(out = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	pt_out = out;
	while (size)
	{
		*pt_out = '\0';
		pt_out++;
		size--;
	}
	*pt_out = '\0';
	return (out);
}
