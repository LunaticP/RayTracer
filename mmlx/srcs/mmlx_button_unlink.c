/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_button_unlink.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:50:01 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 07:59:01 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_button_unlink(int id, t_mmlx *win)
{
	int		i;

	i = 0;
	if (0 <= id && id < DFLT_MAX_BUTTONWIN)
	{
		win->button_used[id] = 0;
		win->button_tab[id].button_status = BUTTON_UNUSED;
		ml_memdel(&win->button_tab[id].data_bp);
		mmlx_error(__func__, mmlx_button_update(win, id));
	}
	else if (id < 0)
	{
		while (i < DFLT_MAX_BUTTONWIN)
		{
			win->button_used[i] = 0;
			win->button_tab[i].button_status = BUTTON_UNUSED;
			mmlx_error(__func__, mmlx_button_update(win, i));
			i++;
		}
		return (mmlx_error(__func__, BUTTON_NEGATIVE_ID));
	}
	else
		return (mmlx_error(__func__, BUTTON_UNUSED_ID));
	return (0);
}
