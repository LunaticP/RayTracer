/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:56:21 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 16:59:17 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

t_server	*server(int status, t_server *serv)
{
	static t_server *saved = NULL;

	if (status)
		saved = serv;
	return (saved);
}
