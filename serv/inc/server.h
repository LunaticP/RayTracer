#ifndef FT_SERVER_H
# define FT_SERVER_H
# define MAX_CLIENT 42
# define BUFF_LEN 1024;
# include <netinet/in.h>

typedef enum	e_error
{
	err_socket,
	err_bind
}				t_error;

typedef struct s_client
{
	int					socket;
	struct sockaddr_in	addr;
	char				buf[BUFF_LEN];
	unsigned int		sock_len;
	int					len;

}				t_client;

void	error_code(int code);
int		create_server(const int port);

#endif
