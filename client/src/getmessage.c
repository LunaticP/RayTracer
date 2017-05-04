/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmessage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:46:59 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 10:50:02 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_client.h>

void getmessage(t_client *c)
{
	char		buf[BUFF_LEN];
	int			l;

	while ((l = read(0, buf, BUFF_LEN)) > 0)
	{
		buf[l] = '\0';
		if (c->sock)
			ft_putstr_fd(buf, c->sock);
		ft_strclr(buf);
	}
}
