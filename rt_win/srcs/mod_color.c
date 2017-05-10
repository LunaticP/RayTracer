/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 20:42:00 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 21:28:54 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt_win.h"

static int	mod_color_string(int posx, int posy, t_mlx *win)
{
	t_stringput		data;
	int				i;

	i = 0;
	while (i < MOD_COLOR_STRING)
	{
		data = g_mod_color[i];
		data.xpos = posx;
		data.ypos = posy;
		if (mmlx_string_create(win, &data) < 0)
			return (rt_win_error(__func__, MMLX_ERROR));
		posy += YLEN_SEP;
		i++;
	}
	return (0);
}

int			mod_color(int posx, int posy, float *pitch, t_mlx *win)
{
	if (rt_win_error(__func__, mod_color_string(posx, posy, win)))
		return (-1);
	if (rt_win_error(__func__, mod_color_slider(posx, posy, pitch, win)))
		return (-1);
	return (0);
}
