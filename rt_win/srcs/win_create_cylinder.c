/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_create_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:32:44 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 09:15:25 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		win_create_cylinder(t_mmlx *parent, t_obj *obj)
{
	float		*pitch;
	t_datawin	data_win;
	t_mmlx		*child;
	int			ret;

	ml_memset(&data_win, 0, sizeof(t_datawin));
	if ((ret = rt_win_getpitch(-1, &pitch)) < 0)
		return (rt_win_error(__func__, -1));
	data_win = (t_datawin){.xwin = WIN_XLEN_EDIT, .ywin = WIN_YLEN_EDIT};
	data_win.name = WIN_NAME_CYLINDER;
	data_win.f_keypress = rt_fkeypress;
	data_win.data_kp = (void*)(uint64_t)ret;
	if (!(child = mmlx_create_child(parent, &data_win)))
	{
		rt_win_error(__func__, rt_fkeypress(DFLT_EXIT, (void*)(uint64_t)ret));
		return (rt_win_error(__func__, MMLX_ERROR));
	}
	if (rt_win_error(__func__, bl_settings_default(obj, child, pitch)))
		return (-1);
	if (rt_win_error(__func__, bl_settings_cylinder(obj, child, pitch)))
		return (-1);
	return (0);
}
