/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:15:51 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 08:07:46 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static void	mmlx_free_button_and_string(t_mlx *win)
{
	size_t		id;

	id = 0;
	while (id < DFLT_MAX_BUTTONWIN)
	{
		ml_memdel(&win->button_tab[id].data_bp);
		id++;
	}
	id = 0;
	while (id < DFLT_MAX_STRINGWIN)
	{
		ml_strdel(&win->string_tab[id].string);
		id++;
	}
}

static void	mmlx_destroy(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, mlx->img_button);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ml_strdel(&(mlx->name));
	mmlx_free_button_and_string(mlx);
}

static void	mmlx_free_struct(t_mlx *mlx)
{
	int		i;

	i = 0;
	mmlx_destroy(mlx);
	while (i < DFLT_MAX_CHILD && mlx->child > 0)
	{
		if (mlx->child_used[i])
			mmlx_close(mlx->child_tab[i]);
		i++;
	}
	if (mlx->id >= DFLT_MAX_PARENT)
		ml_memdel((void**)&mlx);
	else if (*(mlx->count) == 0)
		exit(0);
}

int			mmlx_close(t_mlx *mlx)
{
	if (mlx->used)
		*(mlx->used) = 0;
	else
		mmlx_error(__func__, UNEXPECTED_ERROR);
	if (mlx->count)
		*(mlx->count) -= 1;
	else
		mmlx_error(__func__, UNEXPECTED_ERROR);
	mmlx_free_struct(mlx);
	return (42);
}
