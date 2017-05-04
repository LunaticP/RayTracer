#include <libft.h>
#include <ft_client.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	create_client(char *addr, int port)
{
	int						sock;
	const struct protoent	*proto = getprotobyname("tcp");
	struct sockaddr_in		sai;
	int						i;

	i = -1;
	port = BASE_PORT + MAX_PORT;
	while (port >= BASE_PORT + MAX_PORT)
	{
		port = BASE_PORT;
		while (i == -1 && port < BASE_PORT + MAX_PORT)
		{
			sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
			if (sock == -1)
				error_code(err_socket);
			sai.sin_family = AF_INET;
			sai.sin_port = htons(port);
			sai.sin_addr.s_addr = inet_addr(addr);
			if ((i = connect(sock, (const struct sockaddr *)&sai,
			sizeof(sai))) == -1)
				port++;
			else
				break;
			close(sock);
		}
		if (port >= BASE_PORT + MAX_PORT)
		{
			ft_putendl("Can't connect... retry");
			sleep(10);
		}
	}
	ft_putnbr_desc("Connected port: ", port);
	return (sock);
}
