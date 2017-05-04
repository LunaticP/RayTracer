/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:31:57 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 10:29:54 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	create_server(void)
{
	int						sock;
	const struct protoent	*proto = getprotobyname("tcp");
	struct sockaddr_in		sai;
	int						ret;
	int						port;

	ret = -1;
	port = BASE_PORT;
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		error_code(err_socket);
	while (ret == -1 && port < BASE_PORT + PORT_MAX)
	{
		sai.sin_family = AF_INET;
		sai.sin_port = htons(port);
		sai.sin_addr.s_addr = htonl(INADDR_ANY);
		if ((ret = bind(sock, (const struct sockaddr *)&sai,
		sizeof(sai))) == -1)
			port++;
		else
			break ;
	}
	if (port >= BASE_PORT + PORT_MAX)
		error_code(err_bind);
	ft_putnbr_desc("Port: ", port);
	listen(sock, MAX_CLIENT);
	return (sock);
}
