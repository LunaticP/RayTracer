/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:02:45 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 15:11:31 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_client.h>
#include <time.h>

static void	get_messagetime()
{
	time_t rawtime;
	struct tm	*tminfo;
	char		*str;

	time( &rawtime );
	tminfo = localtime ( &rawtime );
	str = ft_strnew(0);
	//tm.tm_hour, tm.tm_min, tm.tm_sec
	str = ft_freejoin(str, "\033[34m[");
	str = ft_freejoin(str, ft_itoa(tminfo->tm_hour));
	str = ft_freejoin(str, ":");
	if (tminfo->tm_min < 10)
		str = ft_freejoin(str, "0");
	str = ft_freejoin(str, ft_itoa(tminfo->tm_min));
	str = ft_freejoin(str, ":");
	if (tminfo->tm_sec < 10)
		str = ft_freejoin(str, "0");
	str = ft_freejoin(str, ft_itoa(tminfo->tm_sec));
	str = ft_freejoin(str, "]\033[0m - ");
	ft_putstr(str);
	//ft_putstr(asctime(timeinfo));
}

void receive(t_client *c)
{
	int			r;
	char		buf[BUFF_LEN];

	ft_putendl("START READ");
	while ((r = recv(c->sock, buf, BUFF_LEN, 0)) != 0)
	{
		if (r == -1)
			continue;
		buf[r] = '\0';
		if (buf[r - 1] == '\n')
			buf[r - 1] = '\0';
		//ft_putstr("RECEIVED: ");
		ft_putchar('\a');
		get_messagetime();
		ft_putendl(buf);
		ft_strclr(buf);
	}
	close(c->sock);
	ft_bzero((void *)c, sizeof(c));
	c->number = -1;
	ft_putendl("END READ");
}
