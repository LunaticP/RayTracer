#ifndef FT_SERVER_H
# define FT_SERVER_H
# define MAX_CLIENT 42
# define PORT_MAX 50
# define BASE_PORT 8327
# define BUFF_LEN 1024
# include <netinet/in.h>

typedef enum	e_error
{
	err_socket,
	err_bind,
	err_connect,
	err_arg
}				t_error;

typedef struct s_client
{
	int					socket;
	int					send_socket;
	struct sockaddr_in	addr;
	char				buf[BUFF_LEN];
	unsigned int		sock_len;
	int					len;
	int					number;
	int					port;
}				t_client;

void	error_code(int code);
int		create_server();
void	client_read(t_client *c_tmp);
int		create_sendclient(t_client *client);
void	message(t_client **c);
int		searchclient(t_client *c, int newc);

#endif
