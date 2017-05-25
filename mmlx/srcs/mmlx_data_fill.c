/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_data_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 00:57:47 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:01:07 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_data_fill(t_mmlx *mlx)
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
