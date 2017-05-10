/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_mouse_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:27:12 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 07:19:55 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_mouse_press(int keycode, int x, int y, t_mlx *mlx)
{
	if (keycode == SLIDER_MOUSE_KEYCODE)
		mmlx_slider_pressed(mlx, x, y);
	mmlx_button_pressed(mlx, x, y, keycode);
	if (mlx->f_mousepress)
		(*(mlx->f_mousepress))(keycode, x, y, mlx->data_mp);
	return (1);
}
