/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:05:06 by aviau             #+#    #+#             */
/*   Updated: 2017/05/21 18:05:08 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

cl_float4		vec_norm(cl_float4 vec)
{
	cl_float4	norm;
	float		lenght;

	lenght = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	norm.x = vec.x / lenght;
	norm.y = vec.y / lenght;
	norm.z = vec.z / lenght;
	return (norm);
}

void		polar_to_vec(float tet, float phi, cl_float4 *dir)
{
	dir->x = sin(tet) * cos(phi);
	dir->z = cos(phi);
	dir->y = sin(tet) * sin(phi);
}

void		vec_to_polar(float *tet, float *phi, cl_float4 dir)
{
	*tet = acos(dir.y);
	*phi = atan2(dir.z, dir.x);
}
