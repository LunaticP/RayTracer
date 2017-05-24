/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 00:36:46 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/25 01:14:53 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

char	*ml_strdup(const char *s1)
{
	char	*dup;
	ssize_t	len;

	len = 0;
	while (s1[len])
		len++;
	if ((dup = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (len >= 0)
	{
		dup[len] = s1[len];
		len--;
	}
	return (dup);
}
