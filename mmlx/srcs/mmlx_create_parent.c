/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_create_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 01:09:06 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/04 14:42:44 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void		mmlx_create_parent_default_param(t_mlx *parent, t_datawin *data)
{
	if (data && data->xwin <= DFLT_MAX_XWIN && data->xwin >= DFLT_MIN_XWIN)
		parent->xwin = data->xwin;
	else
		parent->xwin = DFLT_XWIN;
	if (data && data->ywin <= DFLT_MAX_YWIN && data->ywin >= DFLT_MIN_YWIN)
		parent->ywin = data->ywin;
	else
		parent->ywin = DFLT_YWIN;
	if (data && !(data->name))
		parent->name = ml_strdup(DFLT_PARENTNAME);
	else
		parent->name = ml_strdup(data->name);
}

t_mlx		*mmlx_create_parent(void *mlx, t_datawin *data)
{
	t_mlx	*parent;

	if (!(parent = mmlx_get_parent(-1)))
	{
		mmlx_error(__func__, NEW_PARENT_ERROR);
		return (NULL);
	}
	mmlx_init_tmlx(parent);
	parent->child = 0;
	*(parent->used) = 1;
	parent->mlx = mlx;
	mmlx_create_parent_default_param(parent, data);
	if (mmlx_error(__func__, mmlx_create_win(parent)))
	{
		*(parent->used) = 0;
		return (NULL);
	}
	mlx_loop_hook(mlx, mmlx_refresh, NULL);
	return (parent);
}
