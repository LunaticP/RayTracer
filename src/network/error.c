/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:27:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 17:43:36 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_network.h>

void	error_code(int code)
{
	if (code == err_socket)
		ft_putendl("Impossible de cree la socket !");
	else if (code == err_bind)
		ft_putendl("bind error");
	else if (code == err_connect)
		ft_putendl("Cannot connect");
	else if (code == err_arg)
		ft_putendl("usage: ./server <port>");
	exit(-1);
}
