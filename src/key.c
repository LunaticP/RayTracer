/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <aviau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 07:43:39 by aviau             #+#    #+#             */
/*   Updated: 2017/05/13 18:54:54 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <rt_network.h>

cl_float4	cl_cross(cl_float4 v1, cl_float4 v2)
{
	cl_float4	ret;

	ret.x = ((v1.y * v2.z) - (v1.z * v2.y));
	ret.y = ((v1.z * v2.x) - (v1.x * v2.z));
	ret.z = ((v1.x * v2.y) - (v1.y * v2.x));
	return(ret);
}

cl_float	cl_dot(cl_float4 v1, cl_float4 v2)
{
	cl_float dp;

	dp = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return(dp);
}

cl_float4	normalize(cl_float4 v1)
{
	float norm = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);

	v1.x /= norm;
	v1.y /= norm;
	v1.z /= norm;

	return(v1);
}

void	trans_cam(t_cam *cam, cl_float4 axis, float dir)
{
	cam->ori.x += axis.x * dir;
	cam->ori.y += axis.y * dir;
	cam->ori.z += axis.z * dir;
}

void	rot_cam(t_cam *cam, cl_float4 axis, float angle)
{
	cl_float4 k = cl_cross(axis, cam->dirx);
	cl_float dp = cl_dot(axis, cam->dirx);
	cam->dirx.x = cam->dirx.x * cos(angle) + k.x * sin(angle)
					+ axis.x * dp * (1 - cos(angle));
	cam->dirx.y = cam->dirx.y * cos(angle) + k.y * sin(angle)
					+ axis.y * dp * (1 - cos(angle));
	cam->dirx.z = cam->dirx.z * cos(angle) + k.z * sin(angle)
					+ axis.z * dp * (1 - cos(angle));
	k = cl_cross(axis, cam->diry);
	dp = cl_dot(axis, cam->diry);
	cam->diry.x = cam->diry.x * cos(angle) + k.x * sin(angle)
					+ axis.x * dp * (1 - cos(angle));
	cam->diry.y = cam->diry.y * cos(angle) + k.y * sin(angle)
					+ axis.y * dp * (1 - cos(angle));
	cam->diry.z = cam->diry.z * cos(angle) + k.z * sin(angle)
					+ axis.z * dp * (1 - cos(angle));
	k = cl_cross(axis, cam->dirz);
	dp = cl_dot(axis, cam->dirz);
	cam->dirz.x = cam->dirz.x * cos(angle) + k.x * sin(angle)
					+ axis.x * dp * (1 - cos(angle));
	cam->dirz.y = cam->dirz.y * cos(angle) + k.y * sin(angle)
					+ axis.y * dp * (1 - cos(angle));
	cam->dirz.z = cam->dirz.z * cos(angle) + k.z * sin(angle)
					+ axis.z * dp * (1 - cos(angle));
	cam->dirx = normalize(cam->dirx);
	cam->diry = normalize(cam->diry);
	cam->dirz = normalize(cam->dirz);
}

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
		*k += POS_YM;
	if (KP_8 && !(*k & ROT_XM))
		*k += ROT_XM;
	if (KP_2 && !(*k & ROT_XP))
		*k += ROT_XP;
	if (KP_7 && !(*k & ROT_ZP))
		*k += ROT_ZP;
	if (KP_9 && !(*k & ROT_ZM))
		*k += ROT_ZM;
	if (KP_4 && !(*k & ROT_YP))
		*k += ROT_YP;
	if (KP_6 && !(*k & ROT_YM))
		*k += ROT_YM;
	if (*k ^ REDRAW && !(SPACE))
		*k |= REDRAW;
}

int		k_rel(int key, void *param)
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
	if (KP_8)
		*k -= ROT_XM;
	if (KP_2)
		*k -= ROT_XP;
	if (KP_7)
		*k -= ROT_ZP;
	if (KP_9)
		*k -= ROT_ZM;
	if (KP_4)
		*k -= ROT_YP;
	if (KP_6)
		*k -= ROT_YM;
	if (SPACE)
	{
		server_render();
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
	if (key & POS_XP)
		trans_cam(&s->cam, s->cam.dirx, 0.2);
	if (key & POS_XM)
		trans_cam(&s->cam, s->cam.dirx, -0.2);
	if (key & POS_YP)
		trans_cam(&s->cam, s->cam.diry, 0.2);
	if (key & POS_YM)
		trans_cam(&s->cam, s->cam.diry, -0.2);
	if (key & POS_ZP)
		trans_cam(&s->cam, s->cam.dirz, 0.2);
	if (key & POS_ZM)
		trans_cam(&s->cam, s->cam.dirz, -0.2);
	if (key & ROT_XP)
		rot_cam(&s->cam, s->cam.dirx, 0.1);
	if (key & ROT_XM)
		rot_cam(&s->cam, s->cam.dirx, -0.1);
	if (key & ROT_YP)
		rot_cam(&s->cam, s->cam.diry, -0.1);
	if (key & ROT_YM)
		rot_cam(&s->cam, s->cam.diry, 0.1);
	if (key & ROT_ZP)
		rot_cam(&s->cam, s->cam.dirz, 0.1);
	if (key & ROT_ZM)
		rot_cam(&s->cam, s->cam.dirz, -0.1);
	if (key & BSPACE)
		s->cam.fast = 0;
	else
		s->cam.fast = 1;
}
