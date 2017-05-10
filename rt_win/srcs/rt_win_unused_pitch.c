/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win_unused_pitch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 21:34:21 by gsimeon           #+#    #+#             */
/*   Updated: 2017/04/26 00:34:27 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		rt_win_unused_pitch(int keypress, void *data)
{
	float	*tmp;

	if (keypress == DFLT_EXIT)
		if (rt_win_getpitch((int)data, &tmp) < 0)
			return (rt_win_error(__func__, -1));
	return (0);
}
