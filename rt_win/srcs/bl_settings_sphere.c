/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_settings_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:10:00 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/07 20:08:34 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int			bl_settings_sphere(t_obj *obj, t_mlx *win, float *pitch)
{
	cl_float	*value;
	t_pos		p;
	int			i;

	p = (t_pos){.x = XPOS_BUTTON_START, .y = YPOS_BUTTON_START + YLEN_SEP * NUM_DFLT_BUTTON};
	i = 0;
	while (i < NUM_SPHERE_BUTTON)
	{
		value = (cl_float*)((uint64_t)obj + g_rt_offset_button_sphere[i]);
		if (rt_win_error(__func__, bl_decr_flt(value, win, pitch, &p)))
			return (-1);
		p.y += YLEN_SEP;
		i++;
	}
	p = (t_pos){.x = XPOS_BUTTON_START + XLEN_SEP, .y = YPOS_BUTTON_START + YLEN_SEP * NUM_DFLT_BUTTON};
	i = 0;
	while (i < NUM_SPHERE_BUTTON)
	{
		value = (cl_float*)((uint64_t)obj + g_rt_offset_button_sphere[i]);
		if (rt_win_error(__func__, bl_incr_flt(value, win, pitch, &p)))
			return (-1);
		p.y += YLEN_SEP;
		i++;
	}
	return (0);
}