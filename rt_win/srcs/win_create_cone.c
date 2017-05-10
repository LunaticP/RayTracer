/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_create_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:26:55 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/02 11:19:43 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static int	cone_init_data(t_datawin *data_win, float **pitch)
{
	int			ret;
	
	ml_memset(data_win, 0, sizeof(t_datawin));
	if ((ret = rt_win_getpitch(-1, pitch)) < 0)
		return (rt_win_error(__func__, -1));
	*data_win = (t_datawin){.xwin = WIN_XLEN_EDIT, .ywin = WIN_YLEN_CONE};
	data_win->name = WIN_NAME_CONE;
	data_win->f_keypress = rt_win_unused_pitch;
	data_win->data_kp = (void*)(uint64_t)ret;
	return (0);
}

int			win_create_cone(t_mlx *parent, t_obj *obj)
{
	float		*pitch;
	t_datawin	data_win;
	t_mlx		*child;

	if (cone_init_data(&data_win, &pitch))
		return(rt_win_error(__func__, -1));
	if (!(child = mmlx_create_child(parent, &data_win)))
	{
		rt_win_error(__func__, rt_win_unused_pitch(DFLT_EXIT,
															data_win.data_kp));
		return (rt_win_error(__func__, MMLX_ERROR));
	}
	if (rt_win_error(__func__, bl_settings_default(obj, child, pitch)))
		return (-1);
	if (rt_win_error(__func__, bl_settings_cone(obj, child, pitch)))
		return (-1);
	return (0);
}
