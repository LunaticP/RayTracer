/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 21:55:44 by jogarcia          #+#    #+#             */
/*   Updated: 2015/11/30 21:55:47 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char *pt_s1;
	char *pt_s2;

	if (n == 0)
		return (0);
	pt_s1 = (char *)s1;
	pt_s2 = (char *)s2;
	while ((*pt_s1 == *pt_s2) && n > 1 && *pt_s1 && *pt_s2)
	{
		pt_s1++;
		pt_s2++;
		n--;
	}
	if ((unsigned char)*pt_s1 > (unsigned char)*pt_s2)
		return (1);
	if ((unsigned char)*pt_s1 < (unsigned char)*pt_s2)
		return (-1);
	return (0);
}
