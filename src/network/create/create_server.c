/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:02:02 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 13:47:18 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

int	create_server(t_server *s)
{
	const struct protoent	*proto = getprotobyname("tcp");
	struct sockaddr_in		sai;
	int						ret;

	ret = -1;
	s->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	s->port = BASE_PORT;
	if (s->sock == -1)
		return (err_socket);
	while (ret == -1 && s->port < BASE_PORT + PORT_MAX)
	{
		sai.sin_family = AF_INET;
		sai.sin_port = htons(s->port);
		sai.sin_addr.s_addr = htonl(INADDR_ANY);
		if ((ret = bind(s->sock, (const struct sockaddr *)&sai,
		sizeof(sai))) == -1)
			s->port++;
		else
			break ;
	}
	if (s->port >= BASE_PORT + PORT_MAX)
		return (err_bind);
	listen(s->sock, MAX_CLIENT);
	return (0);
}
