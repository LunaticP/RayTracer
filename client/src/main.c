/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:23:41 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 14:00:50 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_client.h>
#include <pthread.h>

static int sf_getid(int sock)
{
	int i;
	char buf[BUFF_LEN];

	i = recv(sock, buf, BUFF_LEN, 0);
	buf[i] = '\0';
	return (ft_atoi(buf));
}


int main(int ac, char **av)
{
	t_client	c;
	int			port;
	pthread_t	pth;

	if (ac < 2)
		error_code(err_arg);
	port = BASE_PORT;
	c.username = ft_strdup(av[2]);
	while (1)
	{
		c.sock = create_client(getaddress(av[1]), port);
		c.number = sf_getid(c.sock);
		//ft_putnbr_endl(c.number);
		pthread_create(&pth, NULL, (void *)&receive, (void *)&c);
		pthread_create(&pth, NULL, (void *)&getmessage, (void *)&c);
		while (c.number >= 0)
			sleep(1);
		ft_putendl("restart connection...");
		sleep(5);
	}
	close(c.sock);
	return (0);
}
