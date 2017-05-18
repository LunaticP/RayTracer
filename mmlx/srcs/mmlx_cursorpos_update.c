/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_cursorpos_update.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 01:17:23 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:00:54 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static void	mmlx_keep_cursor_inside_win(t_mmlx *mlx, t_slideon *slider)
{
	if (slider->cursor_pos_x >= mlx->xwin - slider->pos_x
													- slider->data.cursor_sizex)
		slider->cursor_pos_x = mlx->xwin - slider->pos_x
												- slider->data.cursor_sizex - 1;
	if (slider->cursor_pos_y >= mlx->ywin - slider->pos_y
													- slider->data.cursor_sizey)
		slider->cursor_pos_y = mlx->ywin - slider->pos_y
												- slider->data.cursor_sizey - 1;
	if (slider->cursor_pos_x < -slider->pos_x)
		slider->cursor_pos_x = -slider->pos_x;
	if (slider->cursor_pos_y < -slider->pos_y)
		slider->cursor_pos_y = -slider->pos_y;
}

static void	mmlx_cursor_inside_slider(t_slideon *slider)
{
	if (slider->cursor_pos_x < -slider->data.cursor_sizex / 2)
		slider->cursor_pos_x = -slider->data.cursor_sizex / 2;
	if (slider->cursor_pos_x >
					slider->data.slider_sizex - slider->data.cursor_sizex / 2)
		slider->cursor_pos_x =
					slider->data.slider_sizex - slider->data.cursor_sizex / 2;
	if (slider->cursor_pos_y < -slider->data.cursor_sizey / 2)
		slider->cursor_pos_y = -slider->data.cursor_sizey / 2;
	if (slider->cursor_pos_y >
					slider->data.slider_sizey - slider->data.cursor_sizey / 2)
		slider->cursor_pos_y =
					slider->data.slider_sizey - slider->data.cursor_sizey / 2;
}

void		mmlx_cursorpos_update(t_mmlx *mlx, t_slideon *slider,
														int pos_x, int pos_y)
{
	slider->old_cursor_pos_x = slider->cursor_pos_x;
	slider->old_cursor_pos_y = slider->cursor_pos_y;
	if ((slider->data.slidertype & ST_CURSOR_XCENTER))
		slider->cursor_pos_x = (slider->data.slider_sizex
											- slider->data.cursor_sizex) / 2;
	if ((slider->data.slidertype & ST_CURSOR_YCENTER))
		slider->cursor_pos_y = (slider->data.slider_sizey
											- slider->data.cursor_sizey) / 2;
	if (!(slider->data.slidertype & ST_CURSOR_XFIXED))
		slider->cursor_pos_x = pos_x - slider->pos_x
												- slider->data.cursor_sizex / 2;
	if (!(slider->data.slidertype & ST_CURSOR_YFIXED))
		slider->cursor_pos_y = pos_y - slider->pos_y
												- slider->data.cursor_sizex / 2;
	if ((slider->data.slidertype & ST_CURSOR_INSIDE))
		mmlx_cursor_inside_slider(slider);
	mmlx_keep_cursor_inside_win(mlx, slider);
}
