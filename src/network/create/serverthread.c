/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverthread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:28:11 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 15:28:18 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

static void	server_error(t_server *s)
{
	ft_putendl("An error occured on server creation...");
	ft_memdel((void **)&s);
}
/*
* thread for the server
* Init the server and keep waiting for clients connections
*/
void		serverthread(void)
{
	t_server	*s;
	int			i;

	s = (t_server *)ft_memalloc(sizeof(s));
	if (create_server(s) != 0)
	{
		server_error(s);
		return ;
	}
	print_info("server created");
	i = 0;
	getserver(0, s);
	show_serverinfo(s);
	print_info("show ok");
	while (i < MAX_CLIENT)
	{
		print_info("waiting a connection...");
		s->c[i].sock = accept(s->sock,
			(struct sockaddr *)&(s->c[i].addr), &(s->c[i].sock_len));
		print_info("Someone trying to connect !");
		if (s->c[i].sock == -1)
			print_error("Socket error");
		s->c[i].id = i;
		s->nb = ++i;
		print_info("starting client thread...");
		pthread_create(&(s->cth[i]), NULL, (void *)client, (void *)&(s->c[i]));
		print_info("new client thread started !");
		//ft_sleep(1);
	}
}
