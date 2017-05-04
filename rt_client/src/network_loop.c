/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 20:11:23 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 21:51:17 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <pthread.h>

static int	sf_getid(int sock)
{
	int i;
	char buf[BUFF_LEN];

	i = recv(sock, buf, BUFF_LEN, 0);
	buf[i] = '\0';
	return (ft_atoi(buf));
}

void		network_loop(char *poste)
{
	pthread_t	pth[2];
	t_client	c;
	int			port;

	port = BASE_PORT;
	while (1)
	{
		c.sock = create_client(poste, port);
		ft_putendl("Client created");
		c.number = 1;//sf_getid(c.sock);
		pthread_create(&pth[0], NULL, (void *)&receive, (void *)&c);//Reception
		while (c.number >= 0)
			sleep(1);
		ft_putendl("restart connection...");
		sleep(5);
	}
	close(c.sock);
}
