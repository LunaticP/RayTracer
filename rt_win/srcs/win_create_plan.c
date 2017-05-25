/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_create_plan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:26:15 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/20 18:53:30 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

static void			init_bg(t_mmlx *child)
{
	void	*img;
	int		width;
	int		height;

	if ((img = mlx_xpm_file_to_image(child->mlx, BG_PLAN, &width, &height)))
	{
		mlx_destroy_image(child->mlx, child->img);
		child->img = img;
		child->data = mlx_get_data_addr(child->img,
								&child->bpp, &child->sizeline, &child->endian);
	}
}

static t_datawin	init_datawin(int ret)
{
	return ((t_datawin){.xwin = WIN_XLEN_EDIT, .ywin = WIN_YLEN_EDIT,
		.name = WIN_NAME_PLAN, .f_keypress = rt_fkeypress,
		.f_close = rt_fclose, .data_kp = (void*)(uint64_t)ret,
		.data_cl = (void*)(uint64_t)ret});
}

int					win_create_plan(t_mmlx *parent, t_obj *obj)
{
	float		*pitch;
	t_datawin	data_win;
	t_mmlx		*child;
	int			ret;

	ml_memset(&data_win, 0, sizeof(t_datawin));
	if ((ret = rt_win_getpitch(-1, &pitch)) < 0)
		return (rt_win_error(__func__, -1));
	data_win = init_datawin(ret);
	if (!(child = mmlx_create_child(parent, &data_win)))
	{
		rt_win_error(__func__, rt_fkeypress(DFLT_EXIT, (void*)(uint64_t)ret));
		return (rt_win_error(__func__, MMLX_ERROR));
	}
	init_bg(child);
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
