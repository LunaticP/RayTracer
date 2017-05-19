/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_create_win.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 00:54:53 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/19 20:51:08 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_create_win(t_mmlx *mlx)
{
	if (!(mlx->win = mlx_new_window(mlx->mlx, mlx->xwin, mlx->ywin, mlx->name)))
		return (mmlx_error(__func__, NEW_WIN_ERROR));
	if (!(mlx->img = mlx_new_image(mlx->mlx, mlx->xwin, mlx->ywin)))
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		return (mmlx_error(__func__, NEW_IMG_ERROR));
	}
	if (!(mlx->img_button = mlx_new_image(mlx->mlx, mlx->xwin, mlx->ywin)))
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		return (mmlx_error(__func__, NEW_IMG_ERROR));
	}
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp,
		&mlx->sizeline, &mlx->endian);
	mlx->data_button = mlx_get_data_addr(mlx->img_button, &mlx->bpp,
		&mlx->sizeline, &mlx->endian);
	mmlx_data_fill(mlx);
	mlx_hook(mlx->win, KEYPRESS, KEYPRESSMASK, mmlx_keypress, mlx);
	mlx_hook(mlx->win, KEYRELEASE, KEYRELEASEMASK, mmlx_keyrelease, mlx);
	mlx_hook(mlx->win, DESTROYNOTIFY, EXPOSUREMASK, mmlx_close, mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, POINTERMOTIONMASK, mmlx_mouse_xy, mlx);
	mlx_hook(mlx->win, BUTTONPRESS, BUTTONPRESSMASK, mmlx_mouse_press, mlx);
	mlx_hook(mlx->win, BUTTONRELEASE, BUTTONRELEASEMASK,
													mmlx_mouse_release, mlx);
	return (0);
}
