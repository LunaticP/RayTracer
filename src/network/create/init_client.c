/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:25:26 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/03 12:36:58 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

void	init_client(t_client *c)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENT)
		ft_bzero((void *)&c[i], sizeof(c[i]));
}
