/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_switchtype_create.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 18:40:58 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 07:01:50 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_check_data(t_switch *src, t_switch *dst)
{
	if (!src->switch_on)
		return (mmlx_error(__func__, SWITCH_ON_NOIMG));
	else if (!src->switch_off)
		return (mmlx_error(__func__, SWITCH_OFF_NOIMG));
	else if (src->size_x <= 0)
		return (mmlx_error(__func__, SWITCH_WRONG_X));
	else if (src->size_y <= 0)
		return (mmlx_error(__func__, SWITCH_WRONG_Y));
	ml_memcpy(dst, src, sizeof(t_switch));
	return (0);
}

int			mmlx_switchtype_create(int id, t_switch *data)
{
	static t_switch		switch_list[DFLT_MAX_SWITCHTYPE];
	static int			switch_used[DFLT_MAX_SWITCHTYPE];
	int					i;

	i = 0;
	if (!data)
		return (mmlx_error(__func__, LACK_DATA));
	else if (0 <= id && id < DFLT_MAX_SWITCHTYPE)
	{
		ml_memcpy(data, &switch_list[id], sizeof(t_switch));
		return (id);
	}
	while (i < DFLT_MAX_SWITCHTYPE && switch_used[i])
		i++;
	if (i < DFLT_MAX_SWITCHTYPE)
	{
		if (mmlx_error(__func__, mmlx_check_data(data, &switch_list[i])) == 0)
		{
			switch_used[i] = 1;
			return (i);
		}
		return (-1);
	}
	else
		return (mmlx_error(__func__, MAX_SWITCHTYPE_ERROR));
}
