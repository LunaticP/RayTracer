/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:52:16 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/12 17:52:24 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN0 static void s_init_base(t_obj *obj)
#define AN1 static int s_choice_data(char **file, int size)
#define AN2 static void s_get_object_var(int index, char *file, t_obj *obj)

AN0;
AN1;
AN2;

static const t_data g_tab_data[] = {
	{"pos{", sizeof(cl_float4), &rt_get_float4_neg},
	{"dir{", sizeof(cl_float4), &rt_get_float3},
	{"tet=", sizeof(cl_float), &rt_get_float},
	{"phi=", sizeof(cl_float), &rt_get_float},
	{"PADDING", 8, &rt_useless},
	{"rot{", sizeof(cl_float4), &rt_get_float3},
	{"min{", sizeof(cl_float4), &rt_get_float3},
	{"max{", sizeof(cl_float4), &rt_get_float3},
	{"col=", sizeof(int), &rt_get_color},
	{"diff=", sizeof(cl_float), &rt_get_float},
	{"refl=", sizeof(cl_float), &rt_get_float},
	{"trans=", sizeof(cl_float), &rt_get_float},
	{"refr=", sizeof(cl_float), &rt_get_float},
	{"PADDING_TYPE", 4, &rt_useless},
	{"r=", sizeof(cl_float), &rt_get_float},
	{"su=", sizeof(cl_float), &rt_get_float},
	{"sd=", sizeof(cl_float), &rt_get_float},
	{"alpha=", sizeof(cl_float), &rt_get_float},
	{"caps=", sizeof(char), &rt_get_char},
	{"PADDING_2", 7, &rt_useless},
	{"p1{", sizeof(cl_float4), &rt_get_float3},
	{"p2{", sizeof(cl_float4), &rt_get_float3},
	{"p3{", sizeof(cl_float4), &rt_get_float3},
	{"mod_tex{", sizeof(cl_float4), &rt_get_float4},
	{"mod_normal{", sizeof(cl_float4), &rt_get_float4},
	{"mod_ref{", sizeof(cl_float4), &rt_get_float4},
	{"mod_trans{", sizeof(cl_float4), &rt_get_float4},
	{"tex=", sizeof(short), &rt_get_short},
	{"n_m=", sizeof(short), &rt_get_short},
	{"r_m=", sizeof(short), &rt_get_short},
	{"t_m=", sizeof(short), &rt_get_short},
	{"}", 0, NULL}
};

void						rt_get_object(t_obj *obj, char *file, int mask_type)
{
	int						index;
	int						check_mask_type;
	int						size;

	check_mask_type = 0;
	size = sizeof(g_tab_data) / sizeof(t_data) - 1;
	rt_check_min_max(&check_mask_type, obj);
	s_init_base(obj);
	while ((index = s_choice_data(&file, size)) != size)
	{
		if (index != 6 && index != 7 &&
				index != 23 && index != 24 && index != 25 && index != 26)
			rt_add_mask(&check_mask_type, index);
		s_get_object_var(index, file, obj);
		if (index == 6)
			obj->min.w = 1;
		if (index == 7)
			obj->max.w = 1;
		file = rt_goto_data_end(file - 1);
	}
	rt_check_all_data(mask_type, check_mask_type);
}

static void					s_init_base(t_obj *obj)
{
	obj->mod_tex = (cl_float3){.x = 1, .y = 1, .z = 0, .w = 0};
	obj->mod_normal = (cl_float3){.x = 1, .y = 1, .z = 0, .w = 0};
	obj->mod_ref = (cl_float3){.x = 1, .y = 1, .z = 0, .w = 0};
	obj->mod_trans = (cl_float3){.x = 1, .y = 1, .z = 0, .w = 0};
}

static int					s_choice_data(char **file, int size)
{
	int						i;

	size += 1;
	i = 0;
	while (i < size)
	{
		if (rt_strcmp(g_tab_data[i].name, *file) == 0)
		{
			*file += ft_strlen(g_tab_data[i].name);
			return (i);
		}
		++i;
	}
	exit_error("EXIT : s_choice_data [rt_get_objects]");
	return (-1);
}

static void					s_get_object_var(int index, char *file, t_obj *obj)
{
	void					*var;
	int						i;
	int						offset;

	if (__builtin_expect(!(obj->type == plan && index == 0), true))
		var = g_tab_data[index].ft_conv(file);
	else
		var = rt_get_float3(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += g_tab_data[i].size;
		++i;
	}
	ft_memcpy((char *)obj + offset, var, g_tab_data[index].size);
}
