/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:12:07 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 12:20:26 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_server.h>

void	message(t_client **c)
{
	int		i;
	int		l;
	char	buf[BUFF_LEN];

	while ((l = read(0, buf, BUFF_LEN)))
	{
		buf[l] = '\0';
		i = 0;
		while (i < MAX_CLIENT)
		{
			if ((*c)[i].socket)
			{
				ft_putnbr_endl(i);
				write((*c)[i].socket, buf, l);
				ft_putnbr_fd(i, (*c)[i].socket);
			}
			i++;
		}
	}
}
