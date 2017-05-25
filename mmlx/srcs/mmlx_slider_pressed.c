/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_slider_pressed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 00:38:10 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_slider_pressed(t_mmlx *mlx, int x, int y)
{
	int		i;
	float	ratio_x;
	float	ratio_y;

	i = 0;
	while (i < DFLT_MAX_SLIDERWIN)
	{
		if (mlx->slider_used[i] && mmlx_onslider(&(mlx->slider_tab[i]), x, y))
		{
			mlx->slider_tab[i].slider_status = SLIDER_PRESSED;
			mmlx_cursorpos_update(mlx, &(mlx->slider_tab[i]), x, y);
			ratio_x = (mlx->slider_tab[i].cursor_pos_x
						+ mlx->slider_tab[i].data.cursor_sizex / 2.0)
						/ (float)mlx->slider_tab[i].data.slider_sizex;
			ratio_y = (mlx->slider_tab[i].cursor_pos_y
						+ mlx->slider_tab[i].data.cursor_sizey / 2)
						/ (float)mlx->slider_tab[i].data.slider_sizey;
			(*(mlx->slider_tab[i].f_slider))(ratio_x, ratio_y,
													mlx->slider_tab[i].data_sm);
		}
		if (mlx->slider_used[i])
			mmlx_error(__func__, mmlx_slider_update(mlx, i));
		i++;
	}
}
