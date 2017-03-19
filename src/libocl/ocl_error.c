/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:16:56 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/04 04:37:59 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_error(cl_int ret, const char *from)
{
	ft_putstr(g_error_array[-ret]);
	ft_putstr(" from function ");
	ft_putendl(from);
	return (0);
}
