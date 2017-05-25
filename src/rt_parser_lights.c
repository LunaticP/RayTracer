/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:33:28 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:33:29 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define MASK_LIGHT		0b00000000000000010100000000001

#define AN1 static t_parser *s_init_new_parser(t_parser *new_parser);
#define AN2 static int s_choice_data(char **file, int size);
#define AN3 static void s_get_light_var(int index, char *file, t_obj *obj);

AN1;
AN2;
AN3;

static const t_data g_tab_data[] = {
	{"pos{", sizeof(cl_float4), &rt_get_float4},
	{"dir{", sizeof(cl_float4), &rt_get_float3},
	{"min{", sizeof(cl_float4), &rt_get_float3},
	{"max{", sizeof(cl_float4), &rt_get_float3},
	{"mod_tex{", sizeof(cl_float4), &rt_get_float4},
	{"mod_normal{", sizeof(cl_float4), &rt_get_float4},
	{"mod_ref{", sizeof(cl_float4), &rt_get_float4},
	{"mod_trans{", sizeof(cl_float4), &rt_get_float4},

	{"diff=", sizeof(cl_float), &rt_get_float},
	{"refl=", sizeof(cl_float), &rt_get_float},
	{"trans=", sizeof(cl_float), &rt_get_float},
	{"r=", sizeof(cl_float), &rt_get_float},

	{"alpha=", sizeof(cl_float), &rt_get_float},
	{"col=", sizeof(int), &rt_get_color},
	{"}", 0, NULL}
};

t_parser			*rt_parser_lights(char *file, t_parser *parser)
{
	t_parser		*new_parser;
	int				mask_check;
	int				index;
	const int		size = sizeof(g_tab_data) / sizeof(t_data) - 1;

	new_parser = NULL;
	mask_check = 0;
	new_parser = s_init_new_parser(new_parser);
	((t_obj *)new_parser->content)->type = light;
	while ((index = s_choice_data(&file, size)) != size)
	{
		rt_add_mask(&mask_check, index);
		s_get_light_var(index, file, (t_obj *)new_parser->content);
		file = rt_goto_data_end(file - 1);
	}
	rt_check_all_data(MASK_LIGHT, mask_check);
	parser->next = new_parser;
	parser = parser->next;
	return (parser);
}

static t_parser		*s_init_new_parser(t_parser *new_parser)
{
	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->content = (t_obj *)rt_memalloc(sizeof(t_obj));
	new_parser->elem = LIGHTS;
	new_parser->next = NULL;
	return (new_parser);
}

static int			s_choice_data(char **file, int size)
{
	int				i;

	i = 0;
	size += 1;
	while (i < size)
	{
		if (rt_strcmp(g_tab_data[i].name, *file) == 0)
		{
			*file += ft_strlen(g_tab_data[i].name);
			return (i);
		}
		++i;
	}
	exit_error("EXIT : s_choice_data [rt_parser_light]");
	return (0);
}

static void			s_get_light_var(int index, char *file, t_obj *obj)
{
	void			*var;
	int				i;
	int				offset;

	var = g_tab_data[index].ft_conv(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += g_tab_data[i].size;
		++i;
	}
	ft_memcpy((char *)obj + offset, var, g_tab_data[index].size);
}
