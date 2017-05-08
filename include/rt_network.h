/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_network.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:59:54 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:43:04 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_NETWORK_H
# define RT_NETWORK_H
# define MAX_CLIENT		42
# define PORT_MAX		50
# define BASE_PORT		1490
# define BUFF_LEN		4
//# define USE_CLUSTER	1
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

typedef enum	e_msgenum
{
	msg_tex,
	msg_part
}				t_msgenum;

typedef struct s_client
{
	int					sock;
	int					send_socket;
	int					type;
	struct sockaddr_in	addr;
	char				*buf;
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

int			init_clustering(t_mlx *mlx, char **av);
int			create_server(t_server *s);
void		init_server(t_server *s);
void		rt_listen(t_server *s);

t_server	*server(int status, t_server *serv);
int			server_render(void);

int			send_message(int type, char *msg, int len, int id_client);
int			parse_msg(char *buf, int len, t_client *c);

void		error_code(int code);

void		print_log(char *str);
void		print_warning(char *str);
void		print_error(char *str);
void		print_info(char *str);

void		*memjoin(char *dst, char *src, int sdst, int ssrc);

#endif
