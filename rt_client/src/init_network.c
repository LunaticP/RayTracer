/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_network.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:49:38 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 18:13:25 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <pthread.h>

int	init_network(char *addr)
{
	t_client	*c;
	pthread_t	cth;

	c = (t_client *)ft_memalloc(sizeof(t_client));
	c->addr = ft_strdup(addr);
	pthread_create(&cth, NULL, (void *)client_loop, (void *)c);
	return (0);
}
