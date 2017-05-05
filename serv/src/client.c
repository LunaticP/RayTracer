/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:27:17 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 15:12:44 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>
#include <time.h>

static void	get_messagetime()
{
	time_t rawtime;
	struct tm	*tminfo;
	char		*str;

	time( &rawtime );
	tminfo = localtime ( &rawtime );
	str = ft_strnew(0);
	//tm.tm_hour, tm.tm_min, tm.tm_sec
	str = ft_freejoin(str, "\033[34m[");
	str = ft_freejoin(str, ft_itoa(tminfo->tm_hour));
	str = ft_freejoin(str, ":");
	if (tminfo->tm_min < 10)
		str = ft_freejoin(str, "0");
	str = ft_freejoin(str, ft_itoa(tminfo->tm_min));
	str = ft_freejoin(str, ":");
	if (tminfo->tm_sec < 10)
		str = ft_freejoin(str, "0");
	str = ft_freejoin(str, ft_itoa(tminfo->tm_sec));
	str = ft_freejoin(str, "]\033[0m - ");
	ft_putstr(str);
}

void	client_read(t_client *c_tmp)
{
	t_client	c;
	char		*msg;

	c = (*c_tmp);
	ft_putstr("\033[32mclient \033[33m");
	ft_putnbr(c.number);
	ft_putendl(" \033[32mis now connected\033[0m");

	msg = ft_strnew(0);
	msg = ft_freejoin(msg, "\033[32mclient \033[33m");
	msg = ft_freejoin(msg, ft_itoa(c.number));
	msg = ft_freejoin(msg, " \033[32mis now connected\033[0m");
	broadcast(msg, c);
	ft_strdel(&msg);
	ft_putnbr_fd(c.number, c.socket);
	while ((c.len = read(c.socket, c.buf, BUFF_LEN)))
	{
		if (c.len > 0)
			c.buf[c.len - 1] = '\0';
		else
			c.buf[c.len] = '\0';
		get_messagetime();
		ft_putendl(c.buf);
		broadcast(c.buf, c);
	}
	ft_putstr("\033[31mclient \033[33m");
	ft_putnbr(c.number);
	ft_putendl(" \033[31mis now disconnected\033[0m");

	msg = ft_strnew(0);
	msg = ft_freejoin(msg, "\033[31mclient \033[33m");
	msg = ft_freejoin(msg, ft_itoa(c.number));
	msg = ft_freejoin(msg, " \033[31mis now disconnected\033[0m");
	broadcast(msg, c);
	ft_strdel(&msg);
	close(c_tmp->socket);
	ft_bzero(c_tmp, sizeof(c));
}
