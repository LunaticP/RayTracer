/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sm_color_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 22:20:49 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 21:13:01 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

void	sm_color_red(float ratiox, float ratioy, void *data)
{
	t_cslider *color;

	ratioy = 0;
	color = (t_cslider*)data;
	*color->color = ((uint32_t)(RED * ratiox) & RED) | (*color->color & ~RED);
	mod_color_block(color->pos.x, color->pos.y, *color->color, color->win);
	rt_win_redraw(NULL);
}
