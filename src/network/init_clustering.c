/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clustering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:44:10 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:40:05 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <rt.h>
#include <pthread.h>

void init_server(t_server *s)
{
	print_log("server starting...");
	create_server(s);
	print_info("server started on port:");
	print_info(ft_itoa(s->port));
	while (s->sock <= 0)
		;
	rt_listen(s);
}

int	create_server(t_server *s)
{
	const struct protoent	*proto = getprotobyname("tcp");
	struct sockaddr_in		sai;
	int						ret;

	ret = -1;
	s->port = BASE_PORT;
	s->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (s->sock == -1)
		error_code(err_socket);
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
		error_code(err_bind);
	listen(s->sock, MAX_CLIENT);
	return (s->sock);
}

int	init_clustering(t_mlx *mlx, char **av)
{
	int			i;
	int			set;
	t_server	*serv;

	i = -1;
	set = USE_CLUSTER;
	if (USE_CLUSTER == 1)
	{
		mlx->cluster = 1;
		serv = ft_memalloc(sizeof(t_server));
		server(1, serv);
		pthread_create(&(mlx->pthserv), NULL,
		(void *)init_server, (void *)serv);
	}
	else
		mlx->cluster = 0;
	return (0);
}
