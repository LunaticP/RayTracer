/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_slider_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:11:37 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static void	mmlx_old_cursorbar(t_mmlx *mlx, int i)
{
	int		x;
	int		y;
	void	*cursor_start;
	int		cursor_x;

	cursor_start = mlx->data_button +
		(mlx->slider_tab[i].pos_x + mlx->slider_tab[i].old_cursor_pos_x)
		* mlx->bpp / 8 + mlx->sizeline *
		(mlx->slider_tab[i].pos_y + mlx->slider_tab[i].old_cursor_pos_y);
	cursor_x = mlx->slider_tab[i].data.cursor_sizex * mlx->bpp / 8;
	y = 0;
	while (y < mlx->slider_tab[i].data.cursor_sizey)
	{
		x = 0;
		while (x < mlx->slider_tab[i].data.cursor_sizex)
		{
			if (mmlx_inside_data_button(mlx, cursor_start + x * mlx->bpp / 8
														+ y * mlx->sizeline))
				((int*)(cursor_start + y * mlx->sizeline))[x] = BG_BUTTON_COLOR;
			x++;
		}
		y++;
	}
}

static void	mmlx_cursorbar(t_mmlx *mlx, char *texture, int i)
{
	int		x;
	int		y;
	void	*cursor_start;
	int		cursor_x;

	cursor_start = mlx->data_button +
		(mlx->slider_tab[i].pos_x + mlx->slider_tab[i].cursor_pos_x)
		* mlx->bpp / 8 + mlx->sizeline *
		(mlx->slider_tab[i].pos_y + mlx->slider_tab[i].cursor_pos_y);
	cursor_x = mlx->slider_tab[i].data.cursor_sizex * mlx->bpp / 8;
	y = 0;
	while (y < mlx->slider_tab[i].data.cursor_sizey)
	{
		x = 0;
		while (x < mlx->slider_tab[i].data.cursor_sizex)
		{
			if (mmlx_inside_data_button(mlx, cursor_start + x * mlx->bpp / 8
					+ y * mlx->sizeline) &&
					((uint32_t*)(texture + cursor_x * y))[x] != BG_BUTTON_COLOR)
				((uint32_t*)(cursor_start + y * mlx->sizeline))[x] =
					((uint32_t*)(texture + cursor_x * y))[x];
			x++;
		}
		y++;
	}
}

static void	mmlx_sliderbar(t_mmlx *mlx, char *texture, int i)
{
	int		x;
	int		y;
	void	*slider_start;
	int		slider_x;

	slider_start = mlx->data_button + mlx->slider_tab[i].pos_x * mlx->bpp / 8 +
					mlx->sizeline * mlx->slider_tab[i].pos_y;
	slider_x = mlx->slider_tab[i].data.slider_sizex * mlx->bpp / 8;
	y = 0;
	while (y < mlx->slider_tab[i].data.slider_sizey)
	{
		x = 0;
		while (x < mlx->slider_tab[i].data.slider_sizex)
		{
			if (mmlx_inside_data_button(mlx, slider_start + x * mlx->bpp / 8
														+ y * mlx->sizeline))
				((int*)(slider_start + y * mlx->sizeline))[x] =
					((int*)(texture + slider_x * y))[x];
			x++;
		}
		y++;
	}
}

static void	mmlx_old_sliderbar(t_mmlx *mlx, int i)
{
	int		x;
	int		y;
	void	*slider_start;
	int		slider_x;

	slider_start = mlx->data_button + mlx->slider_tab[i].pos_x * mlx->bpp / 8 +
					mlx->sizeline * mlx->slider_tab[i].pos_y;
	slider_x = mlx->slider_tab[i].data.slider_sizex * mlx->bpp / 8;
	y = 0;
	while (y < mlx->slider_tab[i].data.slider_sizey)
	{
		x = 0;
		while (x < mlx->slider_tab[i].data.slider_sizex)
		{
			if (mmlx_inside_data_button(mlx, slider_start + x * mlx->bpp / 8
														+ y * mlx->sizeline))
				((int*)(slider_start + y * mlx->sizeline))[x] = BG_BUTTON_COLOR;
			x++;
		}
		y++;
	}
}

int			mmlx_slider_update(t_mmlx *mlx, int i)
{
	mmlx_old_cursorbar(mlx, i);
	if (!mlx->slider_used[i])
		mmlx_old_sliderbar(mlx, i);
	else
	{
		mmlx_sliderbar(mlx, mlx->slider_tab[i].data.slider, i);
		mmlx_cursorbar(mlx, mlx->slider_tab[i].data.cursor, i);
	}
	return (0);
}
