/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_color_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 02:13:17 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

void	mod_color_block(int posx, int posy, uint32_t color, t_mmlx *win)
{
	int		x;
	int		y;
	int		start_x;
	int		start_y;

	start_x = posx + MOD_COLOR_SPACE_X;
	start_y = posy + (MAX_COLOR_Y + MOD_COLOR_SPACE_Y)
		* MOD_COLOR_SLIDER + MOD_COLOR_SPACE_Y + YSIZE_STR;
	y = 0;
	while (y < MOD_COLOR_BLOCK_Y)
	{
		x = 0;
		while (x < MOD_COLOR_BLOCK_X)
		{
			if (x > 0 && y > 0 && x < win->xwin && y < win->ywin)
			{
				((int*)(win->data_button + (start_y + y) *
										win->sizeline))[start_x + x] = color;
			}
			x++;
		}
		y++;
	}
}
