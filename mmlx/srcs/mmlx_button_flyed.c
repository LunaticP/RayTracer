/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_button_flyed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 21:23:52 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 07:58:23 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void		mmlx_button_flyed(t_mmlx *mlx, int x, int y)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_BUTTONWIN)
	{
		if (mlx->button_used[i] && mmlx_onbutton(&(mlx->button_tab[i]), x, y))
		{
			if (!(mlx->button_tab[i].button_status & BUTTON_PRESSED))
				mlx->button_tab[i].button_status = BUTTON_FLYED;
		}
		else if (mlx->button_used[i] &&
						!(mlx->button_tab[i].button_status & BUTTON_DEFAULT))
			mlx->button_tab[i].button_status = BUTTON_DEFAULT;
		if (mlx->button_used[i])
			mmlx_error(__func__, mmlx_button_update(mlx, i));
		i++;
	}
}
