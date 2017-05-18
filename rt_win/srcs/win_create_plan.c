/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_create_plan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:26:15 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 09:14:24 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		win_create_plan(t_mmlx *parent, t_obj *obj)
{
	float		*pitch;
	t_datawin	data_win;
	t_mmlx		*child;
	int			ret;

	ml_memset(&data_win, 0, sizeof(t_datawin));
	if ((ret = rt_win_getpitch(-1, &pitch)) < 0)
		return (rt_win_error(__func__, -1));
	data_win = (t_datawin){.xwin = WIN_XLEN_EDIT, .ywin = WIN_YLEN_EDIT,
		.name = WIN_NAME_PLAN, .f_keypress = rt_fkeypress, .f_close = rt_fclose,
		.data_kp = (void*)(uint64_t)ret, .data_cl = (void*)(uint64_t)ret};
	if (!(child = mmlx_create_child(parent, &data_win)))
	{
		rt_win_error(__func__, rt_fkeypress(DFLT_EXIT, (void*)(uint64_t)ret));
		return (rt_win_error(__func__, MMLX_ERROR));
	}
	if (rt_win_error(__func__, bl_settings_default(obj, child, pitch)))
		return (-1);
	if (rt_win_error(__func__, mod_pitch(MOD_PITCH_XSTART, MOD_PITCH_YSTART,
																pitch, child)))
		return (-1);
	if (rt_win_error(__func__, mod_color(MOD_COLOR_XSTART, MOD_COLOR_YSTART,
															&obj->col, child)))
		return (-1);
	return (0);
}
