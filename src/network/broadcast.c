#include <rt_network.h>
#include <libft.h>

void	broadcast(int type, unsigned char *msg, int len)
{
	int i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		send_message(type, msg, len, i);
		i++;
	}
}
