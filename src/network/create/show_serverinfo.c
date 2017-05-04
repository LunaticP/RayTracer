/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_serverinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:37:58 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/04 13:49:10 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

int	show_serverinfo(t_server *s)
{
	ft_putstr("Server started on port ");
	ft_putnbr(s->port);
	ft_putchar('\n');
	return (0);
}
