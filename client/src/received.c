/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:02:45 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 10:58:26 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_client.h>

void receive(t_client *c)
{
	int			r;
	char		buf[BUFF_LEN];

	ft_putendl("START READ");
	while ((r = recv(c->sock, buf, BUFF_LEN, 0)) != 0)
	{
		if (r == -1)
			continue;
		buf[r] = '\0';
		if (buf[r - 1] == '\n')
			buf[r - 1] = '\0';
		ft_putstr("RECEIVED: ");
		ft_putendl(buf);
		ft_strclr(buf);
	}
	close(c->sock);
	ft_bzero((void *)c, sizeof(c));
	c->number = 0;
	ft_putendl("END READ");
}
