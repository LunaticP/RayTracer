/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_mouse_xy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:26:19 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 07:20:17 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_mouse_xy(int x, int y, t_mlx *mlx)
{
	mmlx_slider_catched(mlx, x, y);
	mmlx_button_flyed(mlx, x, y);
	if (mlx->f_followmouse)
		(*(mlx->f_followmouse))(x, y, mlx->data_fm);
	return (0);
}
