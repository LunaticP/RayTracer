/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_create_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 01:09:06 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 09:41:37 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void		mmlx_create_parent_default_param(t_mmlx *parent, t_datawin *data)
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

t_mmlx		*mmlx_create_parent(void *mlx, t_datawin *data)
{
	t_mmlx	*parent;

	if (!(parent = mmlx_get_parent(-1)))
	{
		mmlx_error(__func__, NEW_PARENT_ERROR);
		return (NULL);
	}
	mmlx_init_tmlx(parent, data);
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
