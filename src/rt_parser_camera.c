/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 01:08:03 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/15 18:15:35 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int s_choice_data(char **file, int size)
#define AN2 static void s_get_camera_var(t_cam *cam, char *file, int index)
#define AN3 static void s_init_parser_content(t_cam *cam)

AN1;
AN2;
AN3;

#define MASK_CAMERA 0b111110011111

static const t_data g_tab_data[] = {
	{"ori{", sizeof(cl_float4), &rt_get_float3},
	{"dirx{", sizeof(cl_float4), &rt_get_float3},
	{"diry{", sizeof(cl_float4), &rt_get_float3},
	{"dirz{", sizeof(cl_float4), &rt_get_float3},
	{"rot{", sizeof(cl_float4), &rt_get_float3},
	{"PADDING_SIZE", sizeof(cl_int2), &rt_useless},
	{"PADDING", 8, &rt_useless},
	{"viewplane{", sizeof(cl_float4), &rt_get_float4_end},
	{"p{", sizeof(cl_float4), &rt_get_float3},
	{"chunk{", sizeof(cl_float2), &rt_get_float2},
	{"fast=", sizeof(short), &rt_get_short},
	{"dsr=", sizeof(short), &rt_get_short},
	{"}", 0, NULL}
};

t_parser					*rt_parser_camera(char *file, t_parser *parser)
{
	t_parser				*new_parser;
	int						mask_check;
	int						index;
	const int				size = sizeof(g_tab_data) / sizeof(t_data) - 1;

	mask_check = 0;
	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->content = (t_cam *)rt_memalloc(sizeof(t_cam));
	new_parser->elem = CAMERA;
	new_parser->next = NULL;
	((t_cam *)(new_parser->content))->size.x = 700;
	((t_cam *)(new_parser->content))->size.y = 900;
	while ((index = s_choice_data(&file, size)) != size)
	{
		rt_add_mask(&mask_check, index);
		s_get_camera_var((t_cam *)new_parser->content, file, index);
		file = rt_goto_data_end(file - 1);
	}
	rt_check_all_data(MASK_CAMERA, mask_check);
	s_init_parser_content(new_parser->content);
	parser->next = new_parser;
	parser = parser->next;
	return (parser);
}

static int					s_choice_data(char **file, int size)
{
	int						i;

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
	exit_error("EXIT : s_choice_data [rt_get_camera]");
	return (-1);
}

static void					s_get_camera_var(t_cam *cam, char *file, int index)
{
	void					*var;
	int						i;
	int						offset;

	var = g_tab_data[index].ft_conv(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += g_tab_data[i].size;
		++i;
	}
	memcpy((char *)cam + offset, var, g_tab_data[index].size);
}

static void					s_init_parser_content(t_cam *cam)
{
	cam->viewplane.x = 10.0 * ((float)WIDTH / (float)HEIGHT);
	cam->viewplane.y = 10.0;
	cam->p.x = -5.0 * ((float)WIDTH / (float)HEIGHT);
	cam->p.y = 5.0;
	cam->p.z = 5;
}
