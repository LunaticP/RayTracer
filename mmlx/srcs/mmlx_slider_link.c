/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_slider_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 12:04:12 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_slider_in_win(t_sliderlink *link, t_slider *data, t_mmlx *mlx)
{
	if (link->pos_x < 0 || link->pos_x + data->slider_sizex >= mlx->xwin)
		return (mmlx_error(__func__, SLIDER_BAD_XPOS));
	else if (link->pos_y < 0 || link->pos_y + data->slider_sizey >= mlx->ywin)
		return (mmlx_error(__func__, SLIDER_BAD_YPOS));
	else if (link->pos_x + link->cursor_pos_x < 0
		|| link->pos_x + link->cursor_pos_x + data->cursor_sizex >= mlx->xwin)
		return (mmlx_error(__func__, CURSOR_BAD_XPOS));
	else if (link->pos_y + link->cursor_pos_y < 0
		|| link->pos_y + link->cursor_pos_y + data->cursor_sizey >= mlx->ywin)
		return (mmlx_error(__func__, CURSOR_BAD_YPOS));
	return (0);
}

static int	mmlx_check_data(t_slideon *dst, t_sliderlink *data, t_mmlx *win)
{
	if (!win || !data)
		return (mmlx_error(__func__, LACK_DATA));
	else if (mmlx_slidertype_create(data->id, &dst->data) != data->id)
		return (mmlx_error(__func__, SLIDER_BAD_ID));
	else if (!(dst->f_slider = data->f_slider))
		return (mmlx_error(__func__, SLIDER_BAD_FUNCTION));
	else if (mmlx_slider_in_win(data, &dst->data, win))
		return (mmlx_error(__func__, -1));
	else if (!data->data_sm || !(dst->data_sm =
			ml_memcpy(malloc(data->data_len), data->data_sm, data->data_len)))
		return (mmlx_error(__func__, SLIDER_BAD_FUNC_DATA));
	return (0);
}

static int	mmlx_slider_freespace(int *i, int *slider_used)
{
	while (*i < DFLT_MAX_SLIDERWIN && slider_used[*i])
		(*i)++;
	if (*i >= DFLT_MAX_SLIDERWIN)
		return (mmlx_error(__func__, MAX_SLIDERWIN_ERROR));
	return (0);
}

int			mmlx_slider_link(t_mmlx *win, t_sliderlink *data)
{
	int			i;

	i = 0;
	if (mmlx_error(__func__, mmlx_slider_freespace(&i, win->slider_used)))
		return (-1);
	if (mmlx_error(__func__, mmlx_check_data(&win->slider_tab[i], data, win)))
		return (-1);
	win->slider_tab[i].slider_status = SLIDER_RELEASED;
	win->slider_tab[i].pos_x = data->pos_x;
	win->slider_tab[i].pos_y = data->pos_y;
	win->slider_tab[i].cursor_pos_x = data->cursor_pos_x;
	win->slider_tab[i].cursor_pos_y = data->cursor_pos_y;
	win->slider_used[i] = 1;
	mmlx_cursorpos_update(win, &win->slider_tab[i],
		data->cursor_pos_x + data->pos_x, data->cursor_pos_y + data->pos_y);
	win->slider_tab[i].old_cursor_pos_x = win->slider_tab[i].cursor_pos_y;
	win->slider_tab[i].old_cursor_pos_y = win->slider_tab[i].cursor_pos_y;
	mmlx_slider_update(win, i);
	return (i);
}
