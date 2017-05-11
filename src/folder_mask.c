#include "parser.h"

void			rt_add_mask(int *mask_check, int index)
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

void			rt_check_min_max(int *mask, t_obj *obj)
{
	if (!(*mask & (1 << 6)))
	{
		*mask |= 1 << 6;
		obj->min = (cl_float4){.x = -FLT_MAX, .y = -FLT_MAX, .z = -FLT_MAX}; // car FLT_MIN = 0
	}
	if (!(*mask & (1 << 7)))
	{
		*mask |= 1 << 7;
		obj->max = (cl_float4){.x = FLT_MAX, .y = FLT_MAX, .z = FLT_MAX};
	}
}
