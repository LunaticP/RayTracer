/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmessage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:22:04 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 13:52:47 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

char	*getmessage(t_client *c)
{
	while ((c->len = recv(c->sock, c->buf, BUFF_LEN, 0)))
		;
	close(c->sock);
	return (NULL);
}
