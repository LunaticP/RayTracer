/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_default.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:17:17 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 17:22:40 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		sc_default(void)
{
	static int	id;
	t_slider	slider;

	if (!id)
	{
		slider.cursor = (char *)g_cursor_default;
		slider.cursor_sizex = CURSOR_DFLT_X;
		slider.cursor_sizey = CURSOR_DFLT_Y;
		slider.slider = (char *)g_slider_default;
		slider.slider_sizex = SLIDER_DFLT_X;
		slider.slider_sizey = SLIDER_DFLT_Y;
		slider.slidertype = ST_CURSOR_YCENTER | ST_CURSOR_INSIDE;
		if ((id = mmlx_slidertype_create(-1, &slider)) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
	}
	return (id);
}
