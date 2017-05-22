/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_switch_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 21:26:16 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static char	*mmlx_fill_unused(t_switchon *data)
{
	uint32_t	*img;
	int			i;

	i = data->data.size_x * data->data.size_y;
	if (!(img = (uint32_t*)malloc(i * sizeof(uint32_t))))
		return (NULL);
	while (i > 0)
	{
		i--;
		img[i] = BG_DFLT_COLOR;
	}
	return ((char*)img);
}

static char	*mmlx_get_img(t_mmlx *mlx, int i)
{
	char	*tmp;

	if (mlx->switch_tab[i].switch_status & SWITCH_ON)
		return (mlx->switch_tab[i].data.switch_on);
	else if (mlx->switch_tab[i].switch_status & SWITCH_OFF)
		return (mlx->switch_tab[i].data.switch_off);
	else if (mlx->switch_tab[i].switch_status & SWITCH_UNUSED)
	{
		if (!(tmp = mmlx_fill_unused(&mlx->switch_tab[i])))
		{
			mmlx_error(__func__, MALLOC_ERROR);
			return (NULL);
		}
		return (tmp);
	}
	else
	{
		mmlx_error(__func__, BAD_STATUS_SWITCH);
		return (NULL);
	}
}

static void	mmlx_stepbystep(t_mmlx *mlx, char *button_img, int i)
{
	int		x;
	int		y;
	void	*button_start;
	int		button_x;

	button_start = mlx->data_button + mlx->switch_tab[i].pos_x * mlx->bpp / 8 +
					mlx->sizeline * mlx->switch_tab[i].pos_y;
	button_x = mlx->switch_tab[i].data.size_x * mlx->bpp / 8;
	y = 0;
	while (y < mlx->switch_tab[i].data.size_y)
	{
		x = 0;
		while (x < mlx->switch_tab[i].data.size_x)
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

int			mmlx_switch_update(t_mmlx *mlx, int i)
{
	char	*img;

	img = mmlx_get_img(mlx, i);
	if (!img)
		return (mmlx_error(__func__, MISSED_IMG));
	mmlx_stepbystep(mlx, img, i);
	if (mlx->switch_tab[i].switch_status & SWITCH_UNUSED)
		ml_strdel(&img);
	return (0);
}
