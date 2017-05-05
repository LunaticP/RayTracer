/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_clustering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:45:56 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 12:59:49 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

int		set_clustering(void)
{
	t_server *s;

	s = getserver(1, NULL);
	if (s != NULL)
		return (s->render = !(s->render));
	return (-1);
}
