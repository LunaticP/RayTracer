/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_create_plan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:26:15 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 20:00:26 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		win_create_plan(t_mlx *parent, t_obj *obj)
{
	float		*pitch;
	t_datawin	data_win;
	t_mlx		*child;
	int			ret;

	ml_memset(&data_win, 0, sizeof(t_datawin));
	if ((ret = rt_win_getpitch(-1, &pitch)) < 0)
		return (rt_win_error(__func__, -1));
	data_win = (t_datawin){.xwin = WIN_XLEN_EDIT, .ywin = WIN_YLEN_PLAN};
	data_win.name = WIN_NAME_PLAN;
	data_win.f_keypress = rt_win_unused_pitch;
	data_win.data_kp = (void*)(uint64_t)ret;
	if (!(child = mmlx_create_child(parent, &data_win)))
	{
		rt_win_error(__func__, rt_win_unused_pitch(DFLT_EXIT,
														(void*)(uint64_t)ret));
		return (rt_win_error(__func__, MMLX_ERROR));
	}
	if (rt_win_error(__func__, bl_settings_default(obj, child, pitch)))
		return (-1);
	if (rt_win_error(__func__, mod_pitch(XPOS_STR_START,
										YPOS_BUTTON_START - 50, pitch, child)))
		return (-1);
	return (0);
}
