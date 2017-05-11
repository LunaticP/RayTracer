/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_network.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:59:54 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/11 14:42:44 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_NETWORK_H
# define RT_NETWORK_H
# define MAX_CLIENT		42
# define PORT_MAX		50
# define BASE_PORT		1490
# define BUFF_LEN		4
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
	msg_tex = 0,
	msg_part = 1
}				t_msgenum;

typedef struct	s_todo
{
	int				line;
	struct s_todo	*next;
}				t_todo;

typedef struct s_client
{
	struct sockaddr_in	addr;
	unsigned char		*buf;
	unsigned int		sock_len;
	int					sock;
	int					send_socket;
	int					type;
	int					len;
	int					id;
	int					pos;
	int					line;
	int					status;
}				t_client;

typedef struct s_server
{
	pthread_t	cth[MAX_CLIENT];
	t_client	c[MAX_CLIENT];
	int			sock;
	int			port;
	int			nb;
	int			c_nb;
	int			render;
	t_todo		*todo;
}				t_server;


int			init_clustering(t_mlx *mlx, char **av);
int			create_server(t_server *s);
void		init_server(t_server *s);
void		rt_listen(t_server *s);

t_server	*server(int status, t_server *serv);
t_mlx		*save_mlx(int status, t_mlx *mlx);

void		change_nbclient(int i);

int			server_render(void);

int			send_message(int type, unsigned char *msg, int len, int id_client);
void		broadcast(int type, unsigned char *msg, int len);
int			parse_msg(unsigned char *buf, int len, t_client *c);

void		error_code(int code);

void		print_log(char *str);
void		print_warning(char *str);
void		print_error(char *str);
void		print_info(char *str);

void		putimg(t_client *c);
void		*memjoin(unsigned char *dst, unsigned char *src, int sdst, int ssrc);

int			init_render(t_server *s);

void		get_newtodo(t_client *c);
void		clear_todo(t_todo *t);
void		remove_todo(void);
int			add_todo(int id);

#endif
