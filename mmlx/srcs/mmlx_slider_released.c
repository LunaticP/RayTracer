/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_slider_released.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 04:30:39 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_slider_released(t_mmlx *mlx, int x, int y)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_SLIDERWIN)
	{
		if (mlx->slider_used[i]
						&& mlx->slider_tab[i].slider_status == SLIDER_PRESSED)
		{
			mlx->slider_tab[i].slider_status = SLIDER_RELEASED;
			mmlx_cursorpos_update(mlx, &(mlx->slider_tab[i]), x, y);
		}
		if (mlx->slider_used[i])
			mmlx_error(__func__, mmlx_slider_update(mlx, i));
		i++;
	}
}
