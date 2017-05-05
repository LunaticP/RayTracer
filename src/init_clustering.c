/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clustering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:31:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 13:53:13 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <pthread.h>
#include <rt_network.h>

int	init_clustering(t_mlx *mlx, char **av)
{
	t_server	*s;

	(void)mlx;
	(void)av;
	if (!(mlx->cluster = USE_CLUSTER))
		return (1);
	//init server
	ft_putendl("\033[33mlog\033[0m - start clustering");
	pthread_create(&(mlx->pthserv), NULL, (void *)&serverthread, NULL);
	s = NULL;
	while ((s = getserver(1, NULL)) == NULL)
		;//Bloque pour initialiser correctement le thread server
	s->render = 0;
	return (0);
}
