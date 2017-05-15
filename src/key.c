/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <aviau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 07:43:39 by aviau             #+#    #+#             */
/*   Updated: 2017/05/15 15:06:00 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	k_press(int key, int *k)
{
	(LEFT && !(*k & POS_XM)) ? *k += POS_XM : 0;
	(RIGHT && !(*k & POS_XP)) ? *k += POS_XP : 0;
	(UP && !(*k & POS_ZP)) ? *k += POS_ZP : 0;
	(DOWN && !(*k & POS_ZM)) ? *k += POS_ZM : 0;
	(P_UP && !(*k & POS_YP)) ? *k += POS_YP : 0;
	(P_DOWN && !(*k & POS_YM)) ? *k += POS_YM : 0;
	(KP_8 && !(*k & ROT_XM)) ? *k += ROT_XM : 0;
	(KP_2 && !(*k & ROT_XP)) ? *k += ROT_XP : 0;
	(KP_7 && !(*k & ROT_ZP)) ? *k += ROT_ZP : 0;
	(KP_9 && !(*k & ROT_ZM)) ? *k += ROT_ZM : 0;
	(KP_4 && !(*k & ROT_YP)) ? *k += ROT_YP : 0;
	(KP_6 && !(*k & ROT_YM)) ? *k += ROT_YM : 0;
	(*k ^ REDRAW && !(SPACE)) ? *k |= REDRAW : 0;
}

int		k_rel(int key, void *param)
{
	int *k;

	k = &((t_mlx*)param)->key;
	(LEFT) ? *k -= POS_XM : 0;
	(RIGHT) ? *k -= POS_XP : 0;
	(UP) ? *k -= POS_ZP : 0;
	(DOWN) ? *k -= POS_ZM : 0;
	(P_UP) ? *k -= POS_YP : 0;
	(P_DOWN) ? *k -= POS_YM : 0;
	(KP_8) ? *k -= ROT_XM : 0;
	(KP_2) ? *k -= ROT_XP : 0;
	(KP_7) ? *k -= ROT_ZP : 0;
	(KP_9) ? *k -= ROT_ZM : 0;
	(KP_4) ? *k -= ROT_YP : 0;
	(KP_6) ? *k -= ROT_YM : 0;
	if (SPACE)
	{
		if (*k & BSPACE)
			*k -= BSPACE;
		else
			*k += BSPACE;
	}
	if (!(*k & REDRAW))
		*k |= REDRAW;
	return (0);
}

void	k_apply(int key, t_scene *s)
{
	(key & POS_XP) ? trans_cam(&s->cam, s->cam.dirx, 0.2) : 0;
	(key & POS_XM) ? trans_cam(&s->cam, s->cam.dirx, -0.2) : 0;
	(key & POS_YP) ? trans_cam(&s->cam, s->cam.diry, 0.2) : 0;
	(key & POS_YM) ? trans_cam(&s->cam, s->cam.diry, -0.2) : 0;
	(key & POS_ZP) ? trans_cam(&s->cam, s->cam.dirz, 0.2) : 0;
	(key & POS_ZM) ? trans_cam(&s->cam, s->cam.dirz, -0.2) : 0;
	(key & ROT_XP) ? rot_cam(&s->cam, s->cam.dirx, 0.1) : 0;
	(key & ROT_XM) ? rot_cam(&s->cam, s->cam.dirx, -0.1) : 0;
	(key & ROT_YP) ? rot_cam(&s->cam, s->cam.diry, -0.1) : 0;
	(key & ROT_YM) ? rot_cam(&s->cam, s->cam.diry, 0.1) : 0;
	(key & ROT_ZP) ? rot_cam(&s->cam, s->cam.dirz, 0.1) : 0;
	(key & ROT_ZM) ? rot_cam(&s->cam, s->cam.dirz, -0.1) : 0;
	if (key & BSPACE)
		s->cam.fast = 0;
	else
		s->cam.fast = 1;
}
