/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:39:20 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/25 03:38:19 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt.h>

void	print_log(char *str)
{
	ft_putstr("\033[90m⦗ log ⦘\033[0m - ");
	ft_putendl(str);
}

void	print_warning(char *str)
{
	ft_putstr("\033[33m⦗ warning ⦘\033[0m - ");
	ft_putendl(str);
}

void	print_error(char *str)
{
	ft_putstr("\033[31m⦗ error ⦘\033[0m - ");
	ft_putendl(str);
}

void	print_info(char *str)
{
	ft_putstr("\033[32m⦗ info ⦘\033[0m - ");
	ft_putendl(str);
}
