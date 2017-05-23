/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder_mask.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 04:43:32 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:21:51 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				rt_add_mask(int *mask_check, int index)
{
	int				check;

	check = 1 << index;
	if (*mask_check & check)
		exit_error("EXIT : s_add_mask [folder_mask.c]");
	*mask_check += check;
}

void				rt_check_all_data(int mask, int check)
{
	if (check == 0 || check != mask)
		exit_error("EXIT : s_check_all_data [folder_mask.c]");
}

void				rt_check_min_max(int *mask, t_obj *obj)
{
	if (!(*mask & (1 << 2)))
	{
		*mask |= 1 << 2;
		obj->min = (cl_float4){\
			.x = -FLT_MAX, .y = -FLT_MAX, .z = -FLT_MAX, .w = 0};
	}
	if (!(*mask & (1 << 3)))
	{
		*mask |= 1 << 3;
		obj->max = (cl_float4){\
			.x = FLT_MAX, .y = FLT_MAX, .z = FLT_MAX, .w = 0};
	}
}
