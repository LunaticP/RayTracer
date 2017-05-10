/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_data_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 00:57:47 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/02 08:15:40 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_data_fill(t_mlx *mlx)
{
	int		*pixel;
	int		i;

	pixel = (int*)mlx->data;
	i = mlx->ywin * mlx->sizeline / sizeof(uint32_t);
	while (i > 0)
	{
		i--;
		pixel[i] = BG_DFLT_COLOR;
	}
	pixel = (int*)mlx->data_button;
	i = mlx->ywin * mlx->sizeline / sizeof(uint32_t);
	while (i > 0)
	{
		i--;
		pixel[i] = BG_BUTTON_COLOR;
	}
}
