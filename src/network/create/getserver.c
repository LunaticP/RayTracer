/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getserver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:21:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/03 12:22:27 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

t_server	*getserver(int state, t_server *s)
{
	static t_server	*server = NULL;

	if (state == 0)
		server = s;
	else
		return (server);
}
