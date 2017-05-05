#include <libft.h>
#include <rt_network.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

void	ft_wait(int t)
{
	time_t	timedelay;
	time_t	start;

	time(&start);
	while (1)
	{
		time(&timedelay);
		if ((timedelay - start) >= t)
			return ;
	}
	return ;
}

int	create_client(t_client *c)
{
	const struct protoent	*proto = getprotobyname("tcp");
	struct sockaddr_in		sai;
	int						i;
	int						port;

	i = -1;
	port = BASE_PORT + MAX_PORT;
	while (port >= BASE_PORT + MAX_PORT)
	{
		port = BASE_PORT;
		while (i == -1 && port < BASE_PORT + MAX_PORT)
		{
			c->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
			if (c->sock == -1)
				error_code(err_socket);
			sai.sin_family = AF_INET;
			sai.sin_port = htons(port);
			sai.sin_addr.s_addr = inet_addr(c->addr);
			if ((i = connect(c->sock, (const struct sockaddr *)&sai,
			sizeof(sai))) == -1)
				port++;
			else
				break;
			close(c->sock);
		}
		if (port >= BASE_PORT + MAX_PORT)
		{
			ft_putendl("Can't connect... retry");
			ft_wait(10);
		}
	}
	print_info(ft_itoa(port));
	return (c->sock);
}
