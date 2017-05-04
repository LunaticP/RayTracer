/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchclient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:18:00 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 10:31:43 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>

int	searchclient(t_client *c, int newc)
{
	int i;

	i = 0;
	while (i < newc)
	{
		if (ft_strcmp((char *)&(c[i].addr),(char *)&(c[newc].addr)) == 0)
		{
			close(c[i].socket);
			ft_bzero((void *)&c[i], sizeof(c[i]));
			return (1);
		}
		i++;
	}
	return (0);
}
