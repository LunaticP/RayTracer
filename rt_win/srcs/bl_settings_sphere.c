/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_settings_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:10:00 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 19:58:49 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static int	button_list(t_obj *obj, t_mmlx *win, float *pitch)
{
	t_pos		p;
	cl_float	*value;
	int			i;

	i = 0;
	p = (t_pos){.x = XPOS_BUTTON_START, .y = YPOS_SPHERE_START};
	if (BUTTON_DIFF_Y > 0)
		p.y += BUTTON_DIFF_Y;
	if (BUTTON_DIFF_X > 0)
		p.x += BUTTON_DIFF_X;
	while (i < NUM_SPHERE_BUTTON)
	{
		value = (cl_float*)((uint64_t)obj + g_rt_offset_button_sphere[i]);
		if (rt_win_error(__func__, bl_decr_flt(value, win, pitch, &p)))
			return (-1);
		p.x += XLEN_SEP;
		if (rt_win_error(__func__, bl_incr_flt(value, win, pitch, &p)))
			return (-1);
		p.x -= XLEN_SEP;
		p.y += YLEN_SEP;
		i++;
	}
	return (0);
}

static int	string_list(t_obj *obj, t_mmlx *win, t_stringput *name_tab,
														t_stringput *value_tab)
{
	t_pos			pos;
	t_stringput		data;
	int				i;

	pos = (t_pos){.x = XPOS_STR_START, .y = YPOS_SPHERE_START};
	i = 0;
	while (i < NUM_SPHERE_PARAM)
	{
		data = name_tab[i];
		data.f_data = (void*)((uint64_t)obj + g_rt_offset_button_sphere[i]);
		data.xpos = pos.x;
		data.ypos = pos.y;
		if (mmlx_string_create(win, &data) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
		data = value_tab[i];
		data.f_data = (void*)((uint64_t)obj + g_rt_offset_button_sphere[i]);
		data.xpos = pos.x;
		data.ypos = pos.y + YLEN_STR_SEP;
		if (mmlx_string_create(win, &data) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
		pos.y += YLEN_SEP;
		i++;
	}
	return (0);
}

int			bl_settings_sphere(t_obj *obj, t_mmlx *win, float *pitch)
{
	if (rt_win_error(__func__, button_list(obj, win, pitch)))
		return (-1);
	if (rt_win_error(__func__, string_list(obj, win,
		(t_stringput*)g_rt_strname_sphere, (t_stringput*)g_rt_strvalue_sphere)))
		return (-1);
	return (0);
}
