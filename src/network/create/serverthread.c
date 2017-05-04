/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverthread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:28:11 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/03 17:55:05 by vthomas          ###   ########.fr       */
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
	int			r;
	int			i;

	s = (t_server *)ft_memalloc(sizeof(s));
	i = 0;
	if (create_server(s) != 0)
	{
		server_error(s);
		return ;
	}
	init_client(s->c);
	getserver(0, s);
	show_serverinfo(s);
	while (i < MAX_CLIENT)
	{
		s->c[i].socket = accept(s->sock,
			(struct sockaddr *)&(s->c[i].addr), &(s->c[i].sock_len));
		if (s->c[i].socket == -1)
			continue;
		s->c[i].id = i;
		s->nb = ++i;
		//CREATE THREAD FOR CLIENT READ
	}
}
