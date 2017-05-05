#ifndef FT_SERVER_H
# define FT_SERVER_H
# define MAX_CLIENT 42
# define MAX_PORT	50
# define BASE_PORT	8327
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
	char				*username;

}				t_client;

void	error_code(int code);
int		create_client(char *addr, int port);
void 	receive(t_client *c);
char	*getaddress(char *poste);
void	getmessage(t_client *c);

#endif
