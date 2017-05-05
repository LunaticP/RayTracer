/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 12:39:45 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 12:46:11 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>

t_client	*client_list(int i, t_client *liste)
{
	static t_client *c = NULL;

	if (i == 0)
		c = liste;
	return (c);
}

void broadcast(char *msg, t_client sender)
{
	t_client	*c;
	int			i;

	c = client_list(1, NULL);
	i = 0;
	while (i < MAX_CLIENT)
	{
		if (c[i].socket)
		{
			if (c[i].socket != sender.socket)
			{
				ft_putstr_fd(msg, c[i].socket);
				//write(c[i].socket, msg, l);
			}
		}
		i++;
	}
}
