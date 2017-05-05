/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:02:45 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 15:31:31 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_network.h>

void receive(t_client *c)
{
	int			r;
	char		buf[BUFF_LEN];

	ft_putendl("START READ");
	write(c->sock, "Hello World", 11);
	while ((r = recv(c->sock, buf, BUFF_LEN, 0)) != 0)
	{
		if (r == -1)
			continue;
		buf[r] = '\0';
		if (buf[r - 1] == '\n')
			buf[r - 1] = '\0';
		//ft_putstr("RECEIVED: ");
		ft_putchar('\a');
		ft_putendl(buf);
		ft_strclr(buf);
	}
	close(c->sock);
	ft_bzero((void *)c, sizeof(c));
	c->number = -1;
	ft_putendl("END READ");
}
