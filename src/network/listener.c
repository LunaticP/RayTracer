/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:46:07 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 11:32:02 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <pthread.h>

void client_listener(t_client *c)
{
	int		ret;
	//char	buf[BUFF_LEN];

	print_log("Thread started");
	send_message(msg_part, "Hello World", 11, 0);
	while ((ret = read(c->sock, (c->buf), BUFF_LEN)) > 0)
	{
		print_info(c->buf);
	}
	print_info("Disconnected");
	close(c->sock);
}

void	rt_listen(t_server *s)
{
	int	i;

	i = 0;
	print_log("Server start listen");
	while (1)
	{
		s->c[i].sock = accept(s->sock, (struct sockaddr *)&(s->c[i].addr),
		&(s->c[i].sock_len));
		print_log("New connection");
		if (s->c[i].sock == -1)
		{
			print_error("Cannot connect client");
			close(s->c[i].sock);
			continue;
		}
		s->c[i].id = i;
		print_log("Start thread");
		pthread_create(&(s->cth[i]), NULL, (void *)&client_listener,
		(void *)&(s->c[i]));
		i++;
	}
	close(s->sock);
}
