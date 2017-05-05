/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmessage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:46:59 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 22:23:28 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_client.h>

void getmessage(t_client *c)
{
	char		buf[BUFF_LEN];
	int			l;
	char		*msg;

	msg = NULL;
	while ((l = read(0, buf, BUFF_LEN)) > 0)
	{
		ft_memdel(&msg);

		msg = ft_strdup(c->username);
		msg = ft_freejoin(msg, ": ");
		buf[l] = '\0';
		msg = ft_freejoin(msg, buf);
		if (c->sock)
			ft_putstr_fd(msg, c->sock);
		ft_strclr(buf);
	}
}
