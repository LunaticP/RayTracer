/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmessage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:22:04 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 15:38:45 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

char	*getmessage(t_client *c)
{
	char	buf[BUFF_LEN];

	//ft_putnbr(c->sock);
	print_log("Start get message for current client");
	if (c->sock == -1)
		print_error("Socket error !");
	print_info(ft_itoa(c->sock));
	while ((c->len = recv(c->sock, buf, BUFF_LEN, 0)) > 0)
	{
		buf[c->len] = '\0';
		ft_putendl(buf);
	}
	print_info(buf);
	if (c->len == -1)
		print_error("Cannot read !");
	close(c->sock);
	ft_bzero(c, sizeof(*c));
	return (NULL);
}
