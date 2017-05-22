/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_slider_unlink.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:31:20 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_slider_unlink(int id, t_mmlx *win)
{
	int		i;

	i = 0;
	if (0 <= id && id < DFLT_MAX_SLIDERWIN)
	{
		win->slider_used[id] = 0;
		win->slider_tab[id].slider_status = SLIDER_RELEASED;
		ml_memdel(&win->slider_tab[id].data_sm);
		mmlx_error(__func__, mmlx_slider_update(win, id));
	}
	else if (id < 0)
	{
		while (i < DFLT_MAX_SLIDERWIN)
		{
			win->slider_used[i] = 0;
			win->slider_tab[i].slider_status = SLIDER_RELEASED;
			mmlx_error(__func__, mmlx_slider_update(win, i));
			i++;
		}
		return (mmlx_error(__func__, SLIDER_NEGATIVE_ID));
	}
	else
		return (mmlx_error(__func__, SLIDER_UNUSED_ID));
	return (0);
}
