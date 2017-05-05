/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clustering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:31:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 11:06:43 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <pthread.h>
#include <rt_network.h>

int	init_clustering(t_mlx *mlx, char **av)
{
	(void)mlx;
	(void)av;
	if (!(mlx->cluster = USE_CLUSTER))
		return (1);
	//init server
	ft_putendl("\033[33mlog\033[0m - start clustering");
	pthread_create(&(mlx->pthserv), NULL, (void *)&serverthread, NULL);
	return (0);
}
