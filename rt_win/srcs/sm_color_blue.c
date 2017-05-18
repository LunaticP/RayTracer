/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sm_color_blue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 22:25:03 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/11 02:12:44 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

void	sm_color_blue(float ratiox, float ratioy, void *data)
{
	t_cslider *color;

	ratioy = 0;
	color = (t_cslider*)data;
	*color->color = ((uint32_t)(BLUE * ratiox) & BLUE) |
														(*color->color & ~BLUE);
	mod_color_block(color->pos.x, color->pos.y, *color->color, color->win);
}
