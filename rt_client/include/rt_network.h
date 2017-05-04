#ifndef FT_SERVER_H
# define FT_SERVER_H
# define MAX_CLIENT 42
# define MAX_PORT	50
//# define BASE_PORT	8025
# define BASE_PORT	1490
# define BUFF_LEN 1024
# include <netinet/in.h>

typedef enum	e_error
{
	err_socket,
	err_connect,
	err_arg
}				t_error;

typedef struct s_client
{
	int					sock;
	int					number;

}				t_client;

void	error_code(int code);
void	init_network(char *arg);
void	network_loop(char *poste);
void 	receive(t_client *c);
int		create_client(char *addr, int port);

#endif
