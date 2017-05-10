/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_button_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:25:18 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 02:15:54 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_check_data(t_clickon *dst, t_buttonlink *data, t_mlx *win)
{
	if (!win || !data)
		return (mmlx_error(__func__, LACK_DATA));
	else if (mmlx_buttontype_create(data->id, &dst->data) != data->id)
		return (mmlx_error(__func__, BUTTON_BAD_ID));
	else if (!(dst->f_button = data->f_bpress))
		return (mmlx_error(__func__, BUTTON_BAD_FUNCTION));
	else if (data->pos_x < 0 || data->pos_x + dst->data.size_x >= win->xwin)
		return (mmlx_error(__func__, BUTTON_BAD_XPOS));
	else if (data->pos_y < 0 || data->pos_y + dst->data.size_y >= win->ywin)
		return (mmlx_error(__func__, BUTTON_BAD_YPOS));
	else if (!data->data_bp || !(dst->data_bp =
			ml_memcpy(malloc(data->data_len), data->data_bp, data->data_len)))
		return (mmlx_error(__func__, BUTTON_BAD_FUNC_DATA));
	dst->button_status = BUTTON_DEFAULT;
	return (0);
}

static int	mmlx_button_freespace(int *i, int *button_used)
{
	while (*i < DFLT_MAX_BUTTONWIN && button_used[*i])
		(*i)++;
	if (*i >= DFLT_MAX_BUTTONWIN)
		return (mmlx_error(__func__, MAX_BUTTONWIN_ERROR));
	return (0);
}

int			mmlx_button_link(t_mlx *win, t_buttonlink *data)
{
	int			i;

	i = 0;
	if (mmlx_error(__func__, mmlx_button_freespace(&i, win->button_used)))
		return (-1);
	if (mmlx_error(__func__, mmlx_check_data(&win->button_tab[i], data, win)))
		return (-1);
	win->button_tab[i].pos_x = data->pos_x;
	win->button_tab[i].pos_y = data->pos_y;
	win->button_used[i] = 1;
	mmlx_button_update(win, i);
	return (i);
}
