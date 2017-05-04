/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:23:41 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 10:56:05 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_client.h>
#include <pthread.h>

int main(int ac, char **av)
{
	t_client	c;
	int			port;
	pthread_t	pth;

	if (ac < 1)
		error_code(err_arg);
	port = BASE_PORT;
	while (1)
	{
		c.sock = create_client(getaddress(av[1]), port);
		c.number = 1;
		//ft_putnbr(sock);
		pthread_create(&pth, NULL, (void *)&receive, (void *)&c);
		pthread_create(&pth, NULL, (void *)&getmessage, (void *)&c);
		while (c.number == 1)
			sleep(1);
		ft_putendl("restart connection...");
		sleep(5);
	}
	close(c.sock);
	return (0);
}
