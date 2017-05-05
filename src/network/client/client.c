/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:43:28 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 13:50:36 by vthomas          ###   ########.fr       */
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

	ft_putendl("start read");
	while (1)
	{
		s = getserver(1, NULL);
		if (s == NULL)
			continue;
		if (s->render == 0)
			ft_putendl("No rendering");
		else
			ft_putendl("Is rendering");
		msg = getmessage(c);
		if (msg == NULL)
		{
			ft_putendl("Disconnected");
			break ;
		}
		//ft_sleep(5);
	}
}
