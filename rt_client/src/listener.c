/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:59:56 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/09 15:49:18 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <pthread.h>
#include <libft.h>

void print_mem(unsigned char *buf, int l)
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
	int				type;
	int				current;
	int				tmp;
	unsigned char	*buf_tmp;

	type = *(int *)(&buf[0]);
	len = recv(c->sock, buf, BUFF_LEN, 0);
	len = *(int *)(&buf[0]);
	current = 0;
	buf_tmp = (unsigned char *)ft_strnew(len);
	//ft_bzero(buf, BUFF_LEN);
	c->buf = (unsigned char *)ft_strnew(0);
	while (current < len)
	{
		tmp = read(c->sock, buf_tmp, len);
		c->buf = (unsigned char *)memjoin(c->buf, buf_tmp, current, len);
		current += tmp;
		ft_bzero(buf_tmp, len);
	}
	c->len = len;
	c->type = type;
	return (type);
}

void parse_callback(t_client *c, int type)
{
	if (type == msg_tex)
		callback_init(c);
}

void	rt_listener(t_client *c)
{
	unsigned char	buf[BUFF_LEN + 1];
	int		l;

	buf[BUFF_LEN] = 0;
	while ((l = (recv(c->sock, buf, BUFF_LEN, 0))))
	{
		l = parse_msg(buf, l, c);
//		print_mem(c->buf, c->len);
		print_log("turn and go to render lol");
		print_info(ft_itoa(l));
		parse_callback(c, l);
		//send_message(msg_tex, "OK", 3, c);
	}
	c->id = 0;//For disconnection
}
