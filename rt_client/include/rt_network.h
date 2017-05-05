#ifndef FT_SERVER_H
# define FT_SERVER_H
# define MAX_CLIENT 42
# define MAX_PORT	50
//# define BASE_PORT	8025
# define BASE_PORT	1490
# define BUFF_LEN 1024
# include <netinet/in.h>
# include <pthread.h>

typedef enum	e_error
{
	err_socket,
	err_connect,
	err_arg
}				t_error;

typedef struct s_client
{
	int					sock;
	int					id;
	char				*addr;

}				t_client;

t_client	*rt_client(int status, t_client *c);

void		ft_wait(int t);

void		error_code(int code);
int			init_network(char *addr);
int			create_client(t_client *c);
void		client_loop(t_client *c);

void		rt_listener(t_client *c);

void		print_log(char *str);
void		print_warning(char *str);
void		print_error(char *str);
void		print_info(char *str);

#endif
