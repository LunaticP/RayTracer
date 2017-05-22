/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_create_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 01:01:18 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 10:50:13 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static void	mmlx_fill_child(t_mmlx *parent, t_datawin *data, int i)
{
	ml_memset(parent->child_tab[i], 0, sizeof(t_mmlx));
	parent->child_tab[i]->mlx = parent->mlx;
	parent->child_tab[i]->count = &(parent->child);
	parent->child_tab[i]->used = &(parent->child_used[i]);
	mmlx_init_tmlx(parent->child_tab[i], data);
	if (data && data->xwin <= DFLT_MAX_XWIN && data->xwin >= DFLT_MIN_XWIN)
		parent->child_tab[i]->xwin = data->xwin;
	else
		parent->child_tab[i]->xwin = DFLT_XWIN_CHILD;
	if (data && data->ywin <= DFLT_MAX_YWIN && data->ywin >= DFLT_MIN_YWIN)
		parent->child_tab[i]->ywin = data->ywin;
	else
		parent->child_tab[i]->ywin = DFLT_YWIN_CHILD;
	if (data && !(data->name))
		parent->child_tab[i]->name = ml_strdup(DFLT_CHILDNAME);
	else
		parent->child_tab[i]->name = ml_strdup(data->name);
}

t_mmlx		*mmlx_create_child(t_mmlx *parent, t_datawin *data)
{
	int		i;

	i = 0;
	while (i < DFLT_MAX_CHILD && parent->child_used[i])
		i++;
	if (i >= DFLT_MAX_CHILD)
	{
		mmlx_error(__func__, MAX_CHILD_ERROR);
		return (NULL);
	}
	if (!(parent->child_tab[i] = (t_mmlx*)malloc(sizeof(t_mmlx))))
	{
		mmlx_error(__func__, NEW_CHILD_ERROR);
		return (NULL);
	}
	mmlx_fill_child(parent, data, i);
	if (!mmlx_error(__func__, mmlx_create_win(parent->child_tab[i])))
	{
		*(parent->child_tab[i]->count) += 1;
		*(parent->child_tab[i]->used) = 1;
		parent->child_tab[i]->id = mmlx_create_id();
		return (parent->child_tab[i]);
	}
	return (NULL);
}
