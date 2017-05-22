/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win_getpitch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 19:56:27 by gsimeon           #+#    #+#             */
/*   Updated: 2017/04/26 00:29:11 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		rt_win_getpitch(int i, float **pitch)
{
	static float	pitch_tab[DFLT_MAX_PITCH];
	static int		used[DFLT_MAX_PITCH];

	if (0 <= i && i < DFLT_MAX_PITCH)
	{
		used[i] = 0;
		*pitch = NULL;
		return (i);
	}
	i = 0;
	while (i < DFLT_MAX_PITCH && used[i])
		i++;
	if (i != DFLT_MAX_PITCH)
	{
		used[i] = 1;
		pitch_tab[i] = 1;
		*pitch = &pitch_tab[i];
		return (i);
	}
	return (rt_win_error(__func__, RT_NO_MORE_PITCH));
}
