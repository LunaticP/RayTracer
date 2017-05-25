/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_default.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:17:17 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/12 16:06:46 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static const t_slider	g_slider = {
	.cursor = (char *)g_cursor,
	.cursor_sizex = CURSOR_DFLT_X,
	.cursor_sizey = CURSOR_DFLT_Y,
	.slider = (char *)g_slider_grey,
	.slider_sizex = SLIDER_DFLT_X,
	.slider_sizey = SLIDER_DFLT_Y,
	.slidertype = ST_CURSOR_YCENTER | ST_CURSOR_INSIDE
};

int		sc_default(void)
{
	static int	id;

	if (!id)
	{
		if ((id = mmlx_slidertype_create(-1, (t_slider*)(&g_slider))) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
