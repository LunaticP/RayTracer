/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:46:07 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/10 22:31:28 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <pthread.h>
#include <errno.h>

static void print_mem(unsigned char *buf, int l)
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

int			parse_msg(unsigned char *buf, int len, t_client *c)
{
	int	current;
	int	tmp;

	ft_memcpy((void *)&(c->type), (void *)c->buf, sizeof(int));
	len = read(c->sock, buf, BUFF_LEN);
	ft_memcpy((void *)&(c->len), (void *)c->buf, sizeof(int));
	if (c->type == msg_part)
	{
		len = read(c->sock, buf, BUFF_LEN);
		ft_memcpy((void *)&(c->pos), (void *)c->buf, sizeof(int));
	}
	current = 0;
	ft_bzero(buf, BUFF_LEN);
	ft_strdel((char **)&(c->buf));
	c->buf = (unsigned char *)ft_strnew(0);
	while (current < c->len)
	{
		tmp = recv(c->sock, buf, BUFF_LEN, 0);
		current += tmp;
		c->buf = (unsigned char *)memjoin(c->buf, buf, current - tmp, BUFF_LEN);
		ft_bzero(buf, BUFF_LEN);
	}
	c->len = len;
	return (c->type);
}

/*
* thread launch for waiting client read
*/
void client_listener(t_client *c)
{
	int		ret;

	print_log("Thread started");
//	send_message(msg_part, (unsigned char *)"Hello World", 12, 0);
	c->buf = (unsigned char *)ft_strnew(4);
	while ((ret = read(c->sock, c->buf, BUFF_LEN)))
	{
		ret = parse_msg(c->buf, ret, c);
		if (ret == msg_part)
		{
			print_info("Part received");
			putimg(c);
			c->status = 0;
		}
		print_mem(c->buf, c->len);
	}
	add_todo(c->line);
	print_info("Disconnected");
	close(c->sock);
	ft_bzero((void **)&c, sizeof(c));
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
		if (errno)
		{
			print_info(ft_itoa(s->sock));
			print_warning(strerror(errno));
		}
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
