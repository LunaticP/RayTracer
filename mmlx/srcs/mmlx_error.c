/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 19:53:17 by jogarcia          #+#    #+#             */
/*   Updated: 2017/04/10 00:16:25 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_error(const char *prefix, int error)
{
	if (error && error > -ENUM_ERROR_SIZE && error < ENUM_ERROR_SIZE)
	{
		if (error > 0)
		{
			ml_putstr_fd(prefix, 2);
			ml_putstr_fd(" : ", 2);
			ml_putendl_fd(g_mmlx_error_array[error], 2);
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
