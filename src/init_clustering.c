/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clustering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:31:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 13:45:02 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <pthread.h>
#include <rt_network.h>

int	init_clustering(t_mlx *mlx, char **av)
{
	if (!(mlx->cluster = useclustering(av)))
		return (1);
	//init server
	pthread_create(&(mlx->pthserv), NULL, (void *)&serverthread, NULL);
	return (0);
}
