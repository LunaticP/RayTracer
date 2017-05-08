/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:59:56 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 20:50:08 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <pthread.h>
#include <libft.h>

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
	int	type;
	int	current;
	int	tmp;

	type = *(int *)(&buf[0]);
	len = recv(c->sock, buf, BUFF_LEN, 0);
	len = *(int *)(&buf[0]);
	current = 0;
	ft_bzero(buf, BUFF_LEN);
	c->buf = (unsigned char *)ft_strnew(0);
	while (current < len)
	{
		tmp = recv(c->sock, buf, BUFF_LEN, 0);
		c->buf = (unsigned char *)memjoin(c->buf, buf, current, BUFF_LEN);
		current += tmp;
		ft_bzero(buf, BUFF_LEN);
	}
	c->len = len;
	c->type = type;
	return (type);
}

void	rt_listener(t_client *c)
{
	unsigned char	buf[BUFF_LEN + 1];
	int		l;
	buf[BUFF_LEN] = 0;
	while ((l = (recv(c->sock, buf, BUFF_LEN, 0))))
	{
		l = parse_msg(buf, l, c);
		print_mem(c->buf, c->len);
		print_log("turn");
		//send_message(msg_tex, "OK", 3, c);
	}
	c->id = 0;//For disconnection
}
