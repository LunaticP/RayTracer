/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:59:56 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 15:43:48 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <pthread.h>
#include <libft.h>

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

	type = (int) *buf;
	len = recv(c->sock, buf, BUFF_LEN, 0);
	len = (int)*buf;
	print_info(ft_itoa(len));
	current = 0;
	ft_bzero(buf, BUFF_LEN);
	c->buf = ft_strnew(0);
	while (current < len)
	{
		tmp= recv(c->sock, buf, BUFF_LEN, 0);
		current += tmp;
		c->buf = (char *)memjoin(c->buf, buf, current - tmp, BUFF_LEN);
		ft_bzero(buf, BUFF_LEN);
	}
	print_info("readed !");
	c->len = len;
	c->type = type;
	return (type);
}

void	rt_listener(t_client *c)
{
	char	buf[BUFF_LEN + 1];
	int		l;
	print_log("listener start");
	buf[BUFF_LEN] = 0;
	while ((l = (recv(c->sock, buf, BUFF_LEN, 0))))
	{
		print_info("Going parse");
		l = parse_msg(buf, l, c);
		print_mem(c->buf, c->len);
	}
	close(c->sock);
	c->id = 0;//For disconnection
}
