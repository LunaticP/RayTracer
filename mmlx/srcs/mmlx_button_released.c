/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_button_released.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 08:09:46 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 07:58:50 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_button_released(t_mmlx *mlx, int x, int y)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_BUTTONWIN)
	{
		if (mlx->button_used[i] && mmlx_onbutton(&(mlx->button_tab[i]), x, y))
		{
			mlx->button_tab[i].button_status = BUTTON_FLYED;
			mmlx_error(__func__, mmlx_button_update(mlx, i));
		}
		else if (mlx->button_used[i])
		{
			mlx->button_tab[i].button_status = BUTTON_DEFAULT;
			mmlx_error(__func__, mmlx_button_update(mlx, i));
		}
		i++;
	}
}
