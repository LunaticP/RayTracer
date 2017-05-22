/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_button_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 21:32:19 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 07:59:17 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static char	*mmlx_fill_unused(t_clickon *button)
{
	uint32_t	*data;
	int			i;

	i = button->data.size_x * button->data.size_y;
	if (!(data = (uint32_t*)malloc(i * sizeof(uint32_t))))
		return (NULL);
	while (i > 0)
	{
		i--;
		data[i] = BG_DFLT_COLOR;
	}
	return ((char*)data);
}

static char	*mmlx_get_img(t_mmlx *mlx, int i)
{
	char	*tmp;

	if (mlx->button_tab[i].button_status & BUTTON_DEFAULT)
		return (mlx->button_tab[i].data.button_default);
	else if (mlx->button_tab[i].button_status & BUTTON_FLYED)
		return (mlx->button_tab[i].data.button_fly);
	else if (mlx->button_tab[i].button_status & BUTTON_PRESSED)
		return (mlx->button_tab[i].data.button_press);
	else if (mlx->button_tab[i].button_status & BUTTON_UNUSED)
	{
		if (!(tmp = mmlx_fill_unused(&mlx->button_tab[i])))
		{
			mmlx_error(__func__, MALLOC_ERROR);
			return (NULL);
		}
		return (tmp);
	}
	else
	{
		mmlx_error(__func__, BAD_STATUS_BUTTON);
		return (NULL);
	}
}

static void	mmlx_stepbystep(t_mmlx *mlx, char *button_img, int i)
{
	int		x;
	int		y;
	void	*button_start;
	int		button_x;

	button_start = mlx->data_button + mlx->button_tab[i].pos_x * mlx->bpp / 8 +
					mlx->sizeline * mlx->button_tab[i].pos_y;
	button_x = mlx->button_tab[i].data.size_x * mlx->bpp / 8;
	y = 0;
	while (y < mlx->button_tab[i].data.size_y)
	{
		x = 0;
		while (x < mlx->button_tab[i].data.size_x)
		{
			if (mmlx_inside_data_button(mlx, button_start + x * mlx->bpp / 8
														+ y * mlx->sizeline))
				((int*)(button_start + y * mlx->sizeline))[x] =
					((int*)(button_img + button_x * y))[x];
			x++;
		}
		y++;
	}
}

int			mmlx_button_update(t_mmlx *mlx, int i)
{
	char	*img;

	img = mmlx_get_img(mlx, i);
	if (!img)
		return (mmlx_error(__func__, MISSED_IMG));
	mmlx_stepbystep(mlx, img, i);
	if (mlx->button_tab[i].button_status & BUTTON_UNUSED)
		ml_strdel(&img);
	return (0);
}
