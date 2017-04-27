/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 07:43:39 by aviau             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/03/28 11:07:03 by aviau            ###   ########.fr       */
=======
/*   Updated: 2017/04/09 23:11:01 by pgourran         ###   ########.fr       */
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	k_press(int key, int *k)
{
	if (LEFT & !(*k & POS_XM))
		*k += POS_XM;
	else if (RIGHT & !(*k & POS_XP))
		*k += POS_XP;
	else if (UP & !(*k & POS_ZP))
		*k += POS_ZP;
	else if (DOWN & !(*k & POS_ZM))
		*k += POS_ZM;
	else if (P_UP & !(*k & POS_YP))
		*k += POS_YP;
	else if (P_DOWN & !(*k & POS_YM))
		*k += POS_YM;
<<<<<<< HEAD
=======
	else if (SPACE & !(*k & BSPACE))
		*k += BSPACE;
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
}

int	k_rel(int key, void *param)
{
	int *k;

	k = &((t_mlx*)param)->key;
	if (LEFT)
		 *k -= POS_XM;
	else if (RIGHT)
		*k -= POS_XP;
	else if (UP)
		*k -= POS_ZP;
	else if (DOWN)
		*k -= POS_ZM;
	else if (P_UP)
		*k -= POS_YP;
	else if (P_DOWN)
		*k -= POS_YM;
<<<<<<< HEAD
=======
	else if (SPACE)
		*k -= BSPACE;
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
	return (0);
}

void	k_apply(int key, t_scene *s)
{
	if (key & POS_XP)
		s->cam.ori.x += 0.001f;
	if (key & POS_XM)
		s->cam.ori.x -= 0.001f;
	if (key & POS_YP)
		s->cam.ori.y += 0.5f;
	if (key & POS_YM)
		s->cam.ori.y -= 0.5f;
	if (key & POS_ZP)
		s->cam.ori.z += 0.5f;
	if (key & POS_ZM)
		s->cam.ori.z -= 0.5f;
}
