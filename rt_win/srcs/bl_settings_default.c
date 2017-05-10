/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_settings_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 22:01:23 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 15:21:02 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static int	slider_list(t_obj *obj, t_mlx *win)
{
	t_pos		pos;
	t_fslider	slider;
	int		i;

	pos = (t_pos){.x = XPOS_SLIDER_START, .y = YPOS_SLIDER_START};
	if (SLIDER_DIFF_Y > 0)
		pos.y += SLIDER_DIFF_Y;
	i = 0;
	while (i < NUM_DFLT_SLIDER)
	{
		slider = g_rt_slider_minmax[i];
		slider.value = (cl_float*)((uint64_t)obj + slider.offset);
		if (rt_win_error(__func__, sl_default_flt(win, &pos, &slider)))
			return (-1);
		pos.y += YLEN_SEP;
		i++;
	}
	return (0);
}

static int	button_list(t_obj *obj, t_mlx *win, float *pitch)
{
	t_pos		p;
	cl_float	*value;
	int			i;

	p = (t_pos){.x = XPOS_BUTTON_START, .y = YPOS_BUTTON_START};
	i = 0;
	if (BUTTON_DIFF_Y < 0)
		p.y -= BUTTON_DIFF_Y;
	while (i < NUM_DFLT_BUTTON)
	{
		value = (cl_float*)((uint64_t)obj + g_rt_offset_button_all_object[i]);
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

static int	string_list(t_obj *obj, t_mlx *win, t_stringput *name_tab,
														t_stringput *value_tab)
{
	t_pos			pos;
	t_stringput		data;
	int				i;

	pos = (t_pos){.x = XPOS_STR_START, .y = YPOS_STR_START};
	i = 0;
	while (i < NUM_DFLT_PARAM)
	{
		data = name_tab[i];
		data.f_data = (void*)((uint64_t)obj + g_rt_offset_button_all_object[i]);
		data.xpos = pos.x;
		data.ypos = pos.y;
		if (mmlx_string_create(win, &data) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
		data = value_tab[i];
		data.f_data = (void*)((uint64_t)obj + g_rt_offset_button_all_object[i]);
		data.xpos = pos.x;
		data.ypos = pos.y + YLEN_STR_SEP;
		if (mmlx_string_create(win, &data) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
		pos.y += YLEN_SEP;
		i++;
	}
	return (0);
}

int			bl_settings_default(t_obj *obj, t_mlx *win, float *pitch)
{
	if (rt_win_error(__func__, button_list(obj, win, pitch)))
		return (-1);
	if (rt_win_error(__func__, string_list(obj, win,
		(t_stringput*)g_rt_strname_allobj, (t_stringput*)g_rt_strvalue_allobj)))
		return (-1);
	if (rt_win_error(__func__, slider_list(obj, win)))
		return (-1);
	return (0);
}
