/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:43:28 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 14:51:53 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

/*
* Function for read data sended by client
* will parse message type and send to specific callback function
*/

void client(t_client *c)
{
	t_server	*s;
	char		*msg;

	while (!c->sock)
		;
	if (c->sock == -1)
		return ;
	while (1)
	{
		s = getserver(1, NULL);
		if (s == NULL)
			continue;
//		if (s->render == 0)
//			print_log("No rendering");
//		else
//			print_log("Is rendering");
		msg = getmessage(c);
		if (msg == NULL)
		{
			print_warning("Disconnected");
			break ;
		}
		//ft_sleep(5);
	}
}
