/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 07:43:39 by aviau             #+#    #+#             */
/*   Updated: 2017/05/02 07:24:04 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	k_press(int key, int *k)
{
	if (LEFT && !(*k & POS_XM))
		*k += POS_XM;
	if (RIGHT && !(*k & POS_XP))
		*k += POS_XP;
	if (UP && !(*k & POS_ZP))
		*k += POS_ZP;
	if (DOWN && !(*k & POS_ZM))
		*k += POS_ZM;
	if (P_UP && !(*k & POS_YP))
		*k += POS_YP;
	if (P_DOWN && !(*k & POS_YM))
		*k += POS_YM;/*
	if (SPACE && !(*k & BSPACE))
	{
		*k += BSPACE;
		ft_putendl("on");
	}
	else if (SPACE && (*k & BSPACE))
	{
		*k -= BSPACE;
		ft_putendl("off");
	}
	printf("0x%X\n0x%X\n\n", *k, BSPACE);*/
	if (*k ^ REDRAW)
		*k += REDRAW;
}

int	k_rel(int key, void *param)
{
	int *k;

	k = &((t_mlx*)param)->key;
	if (LEFT)
		 *k -= POS_XM;
	if (RIGHT)
		*k -= POS_XP;
	if (UP)
		*k -= POS_ZP;
	if (DOWN)
		*k -= POS_ZM;
	if (P_UP)
		*k -= POS_YP;
	if (P_DOWN)
		*k -= POS_YM;
	if (*k ^ REDRAW)
		*k += REDRAW;
	return (0);
}

void	k_apply(int key, t_scene *s)
{
	if (key & POS_XP)
		s->cam.ori.x += 0.5f;
	if (key & POS_XM)
		s->cam.ori.x -= 0.5f;
	if (key & POS_YP)
		s->cam.ori.y += 0.5f;
	if (key & POS_YM)
		s->cam.ori.y -= 0.5f;
	if (key & POS_ZP)
		s->cam.ori.z += 0.5f;
	if (key & POS_ZM)
		s->cam.ori.z -= 0.5f;
}
