/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_network.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 20:09:31 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 20:40:06 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_network.h>
#include <pthread.h>

void	init_network(char *arg)
{
	pthread_t	pth;

	pthread_create(&pth, NULL, (void *)network_loop, arg);
}
