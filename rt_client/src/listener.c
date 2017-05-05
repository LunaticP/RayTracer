/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:59:56 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 19:22:26 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <pthread.h>
#include <libft.h>

void	rt_listener(t_client *c)
{
	char	buf[BUFF_LEN];
	print_log("listener start");
//TODO: read function here
//	while (recv(c->sock, buf, BUFF_LEN, 0))
//	{
//		ft_putendl(buf);
//	}
}
