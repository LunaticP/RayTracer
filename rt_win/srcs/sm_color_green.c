/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sm_color_green.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 22:24:26 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 21:13:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

void	sm_color_green(float ratiox, float ratioy, void *data)
{
	t_cslider *color;

	ratioy = 0;
	color = (t_cslider*)data;
	*color->color = ((uint32_t)(GREEN * ratiox) & GREEN) |
													(*color->color & ~GREEN);
	mod_color_block(color->pos.x, color->pos.y, *color->color, color->win);
	rt_win_redraw(NULL);
}
