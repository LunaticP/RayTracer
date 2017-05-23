/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:05:06 by aviau             #+#    #+#             */
/*   Updated: 2017/05/23 06:32:04 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

cl_float4	vec_norm(cl_float4 vec)
{
	cl_float4	norm;
	float		lenght;

	lenght = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	norm.x = vec.x / lenght;
	norm.y = vec.y / lenght;
	norm.z = vec.z / lenght;
	return (norm);
}
