/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:22:07 by jogarcia          #+#    #+#             */
/*   Updated: 2015/11/30 16:02:52 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_find(const char *meule, const char *aiguille)
{
	while ((*aiguille && *meule) && (*meule == *aiguille))
	{
		meule++;
		aiguille++;
	}
	if (*aiguille == '\0')
		return (1);
	else
		return (0);
}

char			*ft_strstr(const char *meule, const char *aiguille)
{
	int				i;

	i = 0;
	if (!*aiguille)
		return ((char *)meule);
	while (*meule)
	{
		if (*meule == *aiguille)
		{
			i = ft_find(meule, aiguille);
			if (i == 1)
				return ((char *)meule);
		}
		meule++;
	}
	return (NULL);
}
