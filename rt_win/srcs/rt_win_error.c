/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:51:47 by gsimeon           #+#    #+#             */
/*   Updated: 2017/04/22 21:41:09 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		rt_win_error(const char *prefix, int error)
{
	if (error && error > -RT_ENUM_ERROR_SIZE && error < RT_ENUM_ERROR_SIZE)
	{
		if (error > 0)
		{
			ml_putstr_fd(prefix, 2);
			ml_putstr_fd(" : ", 2);
			ml_putendl_fd(g_rt_win_error_array[error], 2);
			return (-error);
		}
		ml_putstr_fd("\t'-> from ", 2);
		ml_putendl_fd(prefix, 2);
		return (error);
	}
	if (error)
		ml_putendl_fd("WTF_ERROR", 2);
	return (0);
}
