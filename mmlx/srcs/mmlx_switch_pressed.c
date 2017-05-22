/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_switch_pressed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:37:25 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_switch_pressed(t_mmlx *mlx, int x, int y)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_SWITCHWIN)
	{
		if (mlx->switch_used[i] && mmlx_onswitch(&(mlx->switch_tab[i]), x, y))
		{
			if (mlx->switch_tab[i].switch_status == SWITCH_ON)
				mlx->switch_tab[i].switch_status = SWITCH_OFF;
			else if (mlx->switch_tab[i].switch_status == SWITCH_OFF)
				mlx->switch_tab[i].switch_status = SWITCH_ON;
			else
				mmlx_error(__func__, BAD_STATUS_SWITCH);
			if (mlx->switch_tab[i].switch_status & (SWITCH_ON | SWITCH_OFF))
				(*(mlx->switch_tab[i].f_switch))(i,
					(mlx->switch_tab[i].switch_status == SWITCH_ON ? 1 : 0),
					mlx->switch_tab[i].data_sp);
		}
		if (mlx->switch_used[i])
			mmlx_error(__func__, mmlx_switch_update(mlx, i));
		i++;
	}
}
