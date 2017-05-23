/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_switch_unlink.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 10:50:28 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_switch_unlink(int id, t_mmlx *win)
{
	int		i;

	i = 0;
	if (0 <= id && id < DFLT_MAX_SWITCHWIN)
	{
		win->switch_used[id] = 0;
		win->switch_tab[id].switch_status = SWITCH_UNUSED;
		ml_memdel(&win->switch_tab[id].data_sp);
		mmlx_error(__func__, mmlx_switch_update(win, id));
	}
	else if (id < 0)
	{
		while (i < DFLT_MAX_SWITCHWIN)
		{
			win->switch_used[i] = 0;
			win->switch_tab[i].switch_status = SWITCH_UNUSED;
			mmlx_error(__func__, mmlx_switch_update(win, i));
			i++;
		}
		return (mmlx_error(__func__, SWITCH_NEGATIVE_ID));
	}
	else
		return (mmlx_error(__func__, SWITCH_UNUSED_ID));
	return (0);
}
