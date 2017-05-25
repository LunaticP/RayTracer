/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_keyrelease.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 09:02:40 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 09:03:24 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_keyrelease(int keycode, t_mmlx *mlx)
{
	if (mlx->f_keyrelease)
	{
		(*(mlx->f_keyrelease))(keycode, mlx->data_kr);
	}
	return (0);
}
