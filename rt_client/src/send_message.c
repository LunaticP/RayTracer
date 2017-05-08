/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:47:45 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:17:08 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

int	send_message(int type, char *msg, int len, t_client *c)
{
	write(c->sock, &type, sizeof(int));
	write(c->sock, &len, sizeof(int));
	write(c->sock, msg, len);
	return (0);
}
