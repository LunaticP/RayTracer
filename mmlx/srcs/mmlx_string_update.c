/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_string_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 06:39:04 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_string_update(t_mmlx *mlx)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_STRINGWIN)
	{
		if (mlx->string_used[i])
		{
			if (mlx->string_tab[i].f_string)
			{
				ml_strdel(&mlx->string_tab[i].string);
				mlx->string_tab[i].string =
					(*(mlx->string_tab[i].f_string))(mlx->string_tab[i].f_data);
			}
			mlx_string_put(mlx->mlx, mlx->win,
						mlx->string_tab[i].xpos, mlx->string_tab[i].ypos,
						mlx->string_tab[i].color, mlx->string_tab[i].string);
		}
		i++;
	}
}
