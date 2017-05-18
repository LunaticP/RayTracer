/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_keypress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:16:04 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:02:22 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_keypress(int keycode, t_mmlx *mlx)
{
	if (mlx->f_keypress)
	{
		(*(mlx->f_keypress))(keycode, mlx->data_kp);
	}
	if (keycode == DFLT_EXIT)
		mmlx_close(mlx);
	return (0);
}
