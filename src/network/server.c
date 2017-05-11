/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:56:21 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/11 12:27:28 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

t_server	*server(int status, t_server *serv)
{
	static t_server *saved = NULL;

	if (status)
		saved = serv;
	return (saved);
}

void		change_nbclient(int i)
{
	t_server	*s;

	s = server(0, NULL);
	if (i == 0)
		s->c_nb++;
	else
		s->c_nb--;
	ft_putstr("current number of client: ");
	ft_putnbr(s->c_nb);
	ft_putchar('\n');
}
