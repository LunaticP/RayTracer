/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:58:09 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 23:25:14 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

t_client	*rt_client(int status, t_client *c)
{
	static t_client *saved = NULL;

	if (status)
		saved = c;
	return (saved);
}

void		client_loop(t_client *c)
{
	pthread_t	pth;

	while (1)
	{
		create_client(c);
		c->id = 1;
		pthread_create(&pth, NULL, (void *)rt_listener, (void *)c);
		while (c->id)
			ft_wait(1);
		print_log("Disconnected");
		ft_wait(1);
		close(c->sock);
	}
}
