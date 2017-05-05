/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_network.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:59:54 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 13:50:49 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_NETWORK_H
# define RT_NETWORK_H
# define MAX_CLIENT		42
# define PORT_MAX		50
# define BASE_PORT		1490
# define BUFF_LEN		1024
# define USE_CLUSTER	1
# include <libft.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <rt.h>

typedef enum	e_error
{
	err_socket,
	err_bind,
	err_connect,
	err_arg
}				t_error;

typedef struct s_client
{
	int					sock;
	int					send_socket;
	struct sockaddr_in	addr;
	char				buf[BUFF_LEN];
	unsigned int		sock_len;
	int					len;
	int					id;
}				t_client;

typedef struct s_server
{
	t_client	c[MAX_CLIENT];
	pthread_t	cth[MAX_CLIENT];
	int			sock;
	int			port;
	int			nb;
	int			render;
}				t_server;

void		serverthread(void);
t_server	*getserver(int state, t_server *s);
int			create_server(t_server *s);
void		init_client(t_client *c);

void		client(t_client *c);
char		*getmessage(t_client *c);

int			init_clustering(t_mlx *mlx, char **av);
int			useclustering(char **av);
int			show_serverinfo(t_server *s);

int			set_clustering(void);

void		ft_sleep(int t);

#endif
