/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:23:41 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 17:55:28 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>
#include <pthread.h>

int	main(int ac, char **av)
{
	int			sock;
	int			port;
	t_client	*c;
	pthread_t	pth[MAX_CLIENT + 1];
	int			i;

	(void)ac;
	(void)av;
	i = 0;
	c = (t_client *)ft_memalloc(sizeof(t_client) * MAX_CLIENT);
	if (c == NULL)
		ft_putendl("MEMORY ERROR");
	pthread_create(&pth[MAX_CLIENT], NULL, (void *)&message, (void *)&c);
	sock = create_server();
	client_list(0, c);
	while (1)
	{
		c[i].socket = accept(sock, (struct sockaddr *)&(c[i].addr),
		&(c[i].sock_len));
		if (c[i].socket == -1)
			error_code(err_socket);
		c[i].number = i;
		ft_putnbr_endl(i);
		pthread_create(&pth[i], NULL, (void *)&client_read, (void *)&c[i]);
		i++;
	}
	while (i)
		close(c[i--].socket);
	close(sock);
	return (0);
}
