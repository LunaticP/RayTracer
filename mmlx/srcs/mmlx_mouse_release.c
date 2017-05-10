/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_mouse_release.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 06:07:50 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 08:17:35 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_mouse_release(int keycode, int x, int y, t_mlx *mlx)
{
	if (keycode == SLIDER_MOUSE_KEYCODE)
		mmlx_slider_released(mlx, x, y);
	mmlx_button_released(mlx, x, y);
	if (mlx->f_mouserelease)
		(*(mlx->f_mouserelease))(keycode, x, y, mlx->data_mp);
	return (1);
}
