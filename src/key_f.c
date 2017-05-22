/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:01:42 by aviau             #+#    #+#             */
/*   Updated: 2017/05/15 15:21:22 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4	cl_cross(cl_float4 v1, cl_float4 v2)
{
	cl_float4	ret;

	ret.x = ((v1.y * v2.z) - (v1.z * v2.y));
	ret.y = ((v1.z * v2.x) - (v1.x * v2.z));
	ret.z = ((v1.x * v2.y) - (v1.y * v2.x));
	return (ret);
}

cl_float	cl_dot(cl_float4 v1, cl_float4 v2)
{
	cl_float dp;

	dp = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (dp);
}

cl_float4	normalize(cl_float4 v1)
{
	float norm;

	norm = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	v1.x /= norm;
	v1.y /= norm;
	v1.z /= norm;
	return (v1);
}

void		trans_cam(t_cam *cam, cl_float4 axis, float dir)
{
	cam->ori.x += axis.x * dir;
	cam->ori.y += axis.y * dir;
	cam->ori.z += axis.z * dir;
}

void		rot_cam(t_cam *c, cl_float4 axis, float a)
{
	cl_float4	k;
	cl_float	dp;

	k = cl_cross(axis, c->dirx);
	dp = cl_dot(axis, c->dirx);
	c->dirx.x = c->dirx.x * cos(a) + k.x * sin(a) + axis.x * dp * (1 - cos(a));
	c->dirx.y = c->dirx.y * cos(a) + k.y * sin(a) + axis.y * dp * (1 - cos(a));
	c->dirx.z = c->dirx.z * cos(a) + k.z * sin(a) + axis.z * dp * (1 - cos(a));
	k = cl_cross(axis, c->diry);
	dp = cl_dot(axis, c->diry);
	c->diry.x = c->diry.x * cos(a) + k.x * sin(a) + axis.x * dp * (1 - cos(a));
	c->diry.y = c->diry.y * cos(a) + k.y * sin(a) + axis.y * dp * (1 - cos(a));
	c->diry.z = c->diry.z * cos(a) + k.z * sin(a) + axis.z * dp * (1 - cos(a));
	k = cl_cross(axis, c->dirz);
	dp = cl_dot(axis, c->dirz);
	c->dirz.x = c->dirz.x * cos(a) + k.x * sin(a) + axis.x * dp * (1 - cos(a));
	c->dirz.y = c->dirz.y * cos(a) + k.y * sin(a) + axis.y * dp * (1 - cos(a));
	c->dirz.z = c->dirz.z * cos(a) + k.z * sin(a) + axis.z * dp * (1 - cos(a));
	c->dirx = normalize(c->dirx);
	c->diry = normalize(c->diry);
	c->dirz = normalize(c->dirz);
}
