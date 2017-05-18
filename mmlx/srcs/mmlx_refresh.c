/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 06:10:34 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/18 16:44:09 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static void	mmlx_refresh_this(t_mmlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	if (mlx->f_loop)
		(*(mlx->f_loop))(mlx->data_lp);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_button, 0, 0);
	mmlx_string_update(mlx);
	mlx_do_sync(mlx->mlx);
}

static void	mmlx_repeat_with_child(t_mmlx *mlx)
{
	int		id;

	id = 0;
	while (id < DFLT_MAX_CHILD)
	{
		if (mlx->child_used[id])
		{
			mmlx_refresh_this(mlx->child_tab[id]);
			mmlx_repeat_with_child(mlx->child_tab[id]);
		}
		id++;
	}
}

int			mmlx_refresh(t_mmlx *mlx)
{
	int		id;

	id = 0;
	while (id < DFLT_MAX_PARENT)
	{
		if ((mlx = mmlx_get_parent(id)))
		{
			mmlx_refresh_this(mlx);
			mmlx_repeat_with_child(mlx);
		}
		id++;
	}
	return (0);
}
