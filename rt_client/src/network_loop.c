/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 20:11:23 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 15:31:21 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <pthread.h>

static void ft_wait(int t)
{
	time_t	timedelay;
	time_t	start;

	time(&start);
	while (1)
	{
		time(&timedelay);
		if ((timedelay - start) >= t)
			return ;
	}
	return ;
}

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
		c.number = 1;
		pthread_create(&pth[0], NULL, (void *)&receive, (void *)&c);//Reception
		while (c.number >= 0)
			ft_wait(1);
		close(c.sock);
		ft_putendl("restart connection...");
		ft_wait(5);
	}
	close(c.sock);
}
