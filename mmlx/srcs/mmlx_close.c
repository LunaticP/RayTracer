/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:15:51 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/19 21:00:22 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static void	mmlx_free_button_and_string(t_mmlx *win)
{
	size_t		id;

	id = 0;
	while (id < DFLT_MAX_BUTTONWIN)
		ml_memdel(&win->button_tab[id++].data_bp);
	id = 0;
	while (id < DFLT_MAX_SLIDERWIN)
		ml_memdel(&win->slider_tab[id++].data_sm);
	id = 0;
	while (id < DFLT_MAX_SWITCHWIN)
		ml_memdel(&win->switch_tab[id++].data_sp);
	id = 0;
	while (id < DFLT_MAX_STRINGWIN)
	{
		ml_strdel(&win->string_tab[id].string);
		id++;
	}
}

static void	mmlx_destroy(t_mmlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, mlx->img_button);
	ml_strdel(&(mlx->name));
	mmlx_free_button_and_string(mlx);
}

static void	mmlx_free_struct(t_mmlx *mlx)
{
	int		i;

	i = 0;
	mmlx_destroy(mlx);
	while (i < DFLT_MAX_CHILD && mlx->child > 0)
	{
		if (mlx->child_used[i])
		{
			mmlx_close(mlx->child_tab[i]);
			mlx_destroy_window(mlx->mlx, mlx->child_tab[i]->win);
		}
		i++;
	}
	if (mlx->id >= DFLT_MAX_PARENT)
		ml_memdel((void**)&mlx);
	else if (*(mlx->count) == 0)
		exit(0);
}

int			mmlx_close(t_mmlx *mlx)
{
	if (mlx->used)
		*(mlx->used) = 0;
	else
		mmlx_error(__func__, UNEXPECTED_ERROR);
	if (mlx->count)
		*(mlx->count) -= 1;
	else
		mmlx_error(__func__, UNEXPECTED_ERROR);
	if (mlx->f_close)
		(*(mlx->f_close))(mlx->data_cl);
	mmlx_free_struct(mlx);
	return (42);
}
