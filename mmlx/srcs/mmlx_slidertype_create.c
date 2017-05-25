/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_slidertype_create.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:01:07 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/06 00:22:46 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_check_data(t_slider *dst, t_slider *src)
{
	if (!src->slider)
		return (mmlx_error(__func__, SLIDER_NOIMG));
	else if (!src->cursor)
		return (mmlx_error(__func__, CURSOR_NOIMG));
	else if (src->slider_sizex <= 0)
		return (mmlx_error(__func__, SLIDER_WRONG_X));
	else if (src->slider_sizey <= 0)
		return (mmlx_error(__func__, SLIDER_WRONG_Y));
	else if (src->cursor_sizex <= 0)
		return (mmlx_error(__func__, CURSOR_WRONG_X));
	else if (src->cursor_sizey <= 0)
		return (mmlx_error(__func__, CURSOR_WRONG_Y));
	ml_memcpy(dst, src, sizeof(t_slider));
	return (0);
}

int			mmlx_slidertype_create(int id, t_slider *data)
{
	static t_slider		slider_list[DFLT_MAX_SLIDERTYPE];
	static int			slider_used[DFLT_MAX_SLIDERTYPE];
	int					i;

	i = 0;
	if (!data)
		return (mmlx_error(__func__, LACK_DATA));
	else if (0 <= id && id < DFLT_MAX_SLIDERTYPE)
	{
		ml_memcpy(data, &slider_list[id], sizeof(t_slider));
		return (id);
	}
	while (i < DFLT_MAX_SLIDERTYPE && slider_used[i])
		i++;
	if (i < DFLT_MAX_SLIDERTYPE)
	{
		if (mmlx_error(__func__, mmlx_check_data(&slider_list[i], data)) == 0)
		{
			slider_used[i] = 1;
			return (i);
		}
		return (-1);
	}
	else
		return (mmlx_error(__func__, MAX_SLIDERTYPE_ERROR));
}
