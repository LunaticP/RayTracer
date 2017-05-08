/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:47:45 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 13:12:18 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

int	send_message(int type, char *msg, int len, int id_client)
{
	t_server	*s;
	int			i;

	s = NULL;
	while (s == NULL)
		s = server(0, NULL);
	i = 0;
	while (i < MAX_CLIENT && id_client != s->c[i].id)
		i++;
	if (i > MAX_CLIENT || s->c[i].sock == 0)
		return (-1);
	write(s->c[i].sock, &type, sizeof(int));
	write(s->c[i].sock, &len, sizeof(int));
	write(s->c[i].sock, msg, len);
	return (0);
}
