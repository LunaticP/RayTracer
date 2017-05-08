/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:46:07 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 17:52:41 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <pthread.h>
#include <errno.h>

static void print_mem(char *buf, int l)
{
	int i;

	i = 0;
	while (i < l)
	{
		printf("%02X ", buf[i]);
		i++;
	}
	printf("\n");
	fflush(NULL);
}

int			parse_msg(char *buf, int len, t_client *c)
{
	int	type;
	int	current;
	int	tmp;

	print_info("Parsing start");
	ft_memcpy((void *)&(c->type), (void *)c->buf, sizeof(int));
	//type = (int)*(c->buf);
	print_warning("type set");
	len = read(c->sock, buf, BUFF_LEN);
	print_log("Readed");
	len = (int)*buf;
	print_info(ft_itoa(len));
	current = 0;
	ft_bzero(buf, BUFF_LEN);
	ft_strdel(&(c->buf));
	c->buf = ft_strnew(0);
	while (current < len)
	{
		tmp = recv(c->sock, buf, BUFF_LEN, 0);
		current += tmp;
		c->buf = (char *)memjoin(c->buf, buf, current - tmp, BUFF_LEN);
		ft_bzero(buf, BUFF_LEN);
	}
	print_info("readed !");
	c->len = len;
	//c->type = type;
	print_mem(c->buf, c->len);
	return (type);
}

/*
* thread launch for waiting client read
*/
void client_listener(t_client *c)
{
	int		ret;
	//char	buf[BUFF_LEN];

	print_log("Thread started");
	send_message(msg_part, "Hello World", 12, 0);
	c->buf = ft_strnew(4);
	while ((ret = read(c->sock, c->buf, BUFF_LEN)))
	{
		print_info("Going parse");
		//printf("%02X%02X%02X%02X\n"c->buf[0])
		print_mem(c->buf, 4);
		ret = parse_msg(c->buf, ret, c);
//		print_mem(c->buf, c->len);
	}
//	while ((ret = read(c->sock, (c->buf), BUFF_LEN)) > 0)
//	{
//		parse_msg(c->buf, ret, &(c->msg));
//		print_mem(c->msg.buf, c->msg.len);
//		//print_info(c->buf);
//	}
	print_info("Disconnected");
	close(c->sock);
}

void	rt_listen(t_server *s)
{
	int	i;

	i = 0;
	print_log("Server start listen");
	//print_error(strerror(errno));
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
