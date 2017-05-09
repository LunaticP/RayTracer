/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:00:07 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/09 16:39:48 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <rt.h>

int	server_render(void)
{
	t_server *serv;

	serv = server(0, NULL);
	if (serv == NULL)
		return (-1);
	serv->render = !serv->render;
	if (serv->render == 1)
		init_render(s);
	return (serv->render);
}
