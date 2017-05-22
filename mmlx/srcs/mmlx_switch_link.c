/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_switch_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 21:01:37 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_check_data(t_switchon *dst, t_switchlink *data, t_mmlx *win)
{
	if (!win || !data)
		return (mmlx_error(__func__, LACK_DATA));
	else if (mmlx_switchtype_create(data->id, &dst->data) != data->id)
		return (mmlx_error(__func__, SWITCH_BAD_ID));
	else if (!(dst->f_switch = data->f_spress))
		return (mmlx_error(__func__, SWITCH_BAD_FUNCTION));
	else if (data->pos_x < 0 || data->pos_x + dst->data.size_x >= win->xwin)
		return (mmlx_error(__func__, SWITCH_BAD_XPOS));
	else if (data->pos_y < 0 || data->pos_y + dst->data.size_y >= win->ywin)
		return (mmlx_error(__func__, SWITCH_BAD_YPOS));
	else if (!data->data_sp || !(dst->data_sp =
			ml_memcpy(malloc(data->data_len), data->data_sp, data->data_len)))
		return (mmlx_error(__func__, SWITCH_BAD_FUNC_DATA));
	dst->switch_status = data->switch_status;
	return (0);
}

static int	mmlx_switch_freespace(int *i, int *switch_used)
{
	while (*i < DFLT_MAX_SWITCHWIN && switch_used[*i])
		(*i)++;
	if (*i >= DFLT_MAX_SWITCHWIN)
		return (mmlx_error(__func__, MAX_SWITCHWIN_ERROR));
	return (0);
}

int			mmlx_switch_link(t_mmlx *win, t_switchlink *data)
{
	int			i;

	i = 0;
	if (mmlx_error(__func__, mmlx_switch_freespace(&i, win->switch_used)))
		return (-1);
	if (mmlx_error(__func__, mmlx_check_data(&win->switch_tab[i], data, win)))
		return (-1);
	win->switch_tab[i].pos_x = data->pos_x;
	win->switch_tab[i].pos_y = data->pos_y;
	win->switch_used[i] = 1;
	mmlx_switch_update(win, i);
	return (i);
}
