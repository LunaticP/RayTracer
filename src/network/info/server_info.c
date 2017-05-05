/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:36:30 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 14:44:05 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

void print_log(char *str)
{
	ft_putstr("\033[90m[ log ]\033[0m - ");
	ft_putendl(str);
}

void print_warning(char *str)
{
	ft_putstr("\033[33m[ warning ]\033[0m - ");
	ft_putendl(str);
}

void print_error(char *str)
{
	ft_putstr("\033[31m[ error ]\033[0m - ");
	ft_putendl(str);
}

void print_info(char *str)
{
	ft_putstr("\033[32m[ info ]\033[0m - ");
	ft_putendl(str);
}
