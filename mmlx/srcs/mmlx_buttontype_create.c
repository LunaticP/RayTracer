/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_create_buttontype.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 21:55:45 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 00:25:27 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_check_data(t_button *src, t_button *dst)
{
	if (!src->button_default)
		return (mmlx_error(__func__, DFLT_BUTTON_NOIMG));
	else if (!src->button_press)
		return (mmlx_error(__func__, PRESS_BUTTON_NOIMG));
	else if (!src->button_fly)
		return (mmlx_error(__func__, FLY_BUTTON_NOIMG));
	else if (src->size_x <= 0)
		return (mmlx_error(__func__, BUTTON_WRONG_X));
	else if (src->size_y <= 0)
		return (mmlx_error(__func__, BUTTON_WRONG_Y));
	ml_memcpy(dst, src, sizeof(t_button));
	return (0);
}

int			mmlx_buttontype_create(int id, t_button *data)
{
	static t_button		button_list[DFLT_MAX_BUTTONTYPE];
	static int			button_used[DFLT_MAX_BUTTONTYPE];
	int					i;

	i = 0;
	if (!data)
		return (mmlx_error(__func__, LACK_DATA));
	else if (0 <= id && id < DFLT_MAX_BUTTONTYPE)
	{
		ml_memcpy(data, &button_list[id], sizeof(t_button));
		return (id);
	}
	while (i < DFLT_MAX_BUTTONTYPE && button_used[i])
		i++;
	if (i < DFLT_MAX_BUTTONTYPE)
	{
		if (mmlx_error(__func__, mmlx_check_data(data, &button_list[i])) == 0)
		{
			button_used[i] = 1;
			return (i);
		}
		return (-1);
	}
	else
		return (mmlx_error(__func__, MAX_BUTTONTYPE_ERROR));
}
