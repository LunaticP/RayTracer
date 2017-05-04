/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:27:17 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 11:11:48 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>

void	client_read(t_client *c_tmp)
{
	t_client c;

	c = (*c_tmp);
	ft_putstr("\033[32mclient \033[33m");
	ft_putnbr(c.number);
	ft_putendl(" \033[32mis now connected\033[0m");
	while ((c.len = read(c.socket, c.buf, BUFF_LEN)))
	{
		if (c.len > 0)
			c.buf[c.len - 1] = '\0';
		else
			c.buf[c.len] = '\0';
		ft_putnbr(c.number);
		ft_putstr(": ");
		ft_putendl(c.buf);
	}
	ft_putstr("\033[31mclient \033[33m");
	ft_putnbr(c.number);
	ft_putendl(" \033[31mis now disconnected\033[0m");
	close(c.socket);
	ft_bzero(&c, sizeof(c));
}
