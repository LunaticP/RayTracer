/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_button_pressed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 21:22:40 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 07:58:33 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_button_pressed(t_mmlx *mlx, int x, int y, int kc)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_BUTTONWIN)
	{
		if (mlx->button_used[i] && mmlx_onbutton(&(mlx->button_tab[i]), x, y))
		{
			mlx->button_tab[i].button_status = BUTTON_PRESSED;
			(*(mlx->button_tab[i].f_button))(i, kc, mlx->button_tab[i].data_bp);
		}
		else if (mlx->button_used[i] &&
						!(mlx->button_tab[i].button_status & BUTTON_DEFAULT))
			mlx->button_tab[i].button_status = BUTTON_DEFAULT;
		if (mlx->button_used[i])
			mmlx_error(__func__, mmlx_button_update(mlx, i));
		i++;
	}
}
