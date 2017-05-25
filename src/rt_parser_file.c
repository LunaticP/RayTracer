/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:33:18 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:33:21 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int s_choice_lvl_1(char **file, int size);
#define AN2 t_parser *s_init_settings(t_parser *parser);
#define AN3 static void s_check_exception(int index, int *check);

AN1;
AN2;
AN3;

static const t_type_elem g_tab_elem[] = {
	{"objects{", &rt_parser_objects},
	{"lights{", &rt_parser_lights},
	{"camera{", &rt_parser_camera},
	{"settings{", &rt_parser_settings},
	{"textures{", &rt_parser_textures},
	{"}", NULL}
};

t_parser				*rt_parser_file(char *file)
{
	t_parser			*parser;
	t_parser			*ptr_parser;
	int					index;
	int					size;
	int					check[2];

	check[0] = 0;
	check[1] = 0;
	parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	ptr_parser = parser;
	size = sizeof(g_tab_elem) / sizeof(t_type_elem) - 1;
	while ((index = s_choice_lvl_1(&file, size)) != size)
	{
		s_check_exception(index, (int *)&check);
		ptr_parser = g_tab_elem[index].ft_elem(file, ptr_parser);
		file = rt_goto_bracket_close(file);
	}
	if (check[0] != 1)
		ptr_parser = s_init_settings(ptr_parser);
	return (parser);
}

static int				s_choice_lvl_1(char **file, int size)
{
	int					i;

	i = 0;
	if (**file == '\0')
	{
		return (size);
	}
	while (i < size)
	{
		if (rt_strcmp(g_tab_elem[i].name, *file) == 0)
		{
			*file += ft_strlen(g_tab_elem[i].name);
			return (i);
		}
		++i;
	}
	return (_(exit_error("EXIT : rt_choice_lvl_1"), false));
}

t_parser				*s_init_settings(t_parser *parser)
{
	t_parser			*new_parser;
	t_set				*set;

	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->elem = SETTINGS;
	new_parser->next = NULL;
	set = (t_set *)rt_memalloc(sizeof(t_parser));
	set->width = 1280;
	set->height = 720;
	set->max_reflect = 20;
	new_parser->content = set;
	parser->next = new_parser;
	parser = parser->next;
	return (parser);
}

static void				s_check_exception(int index, int *check)
{
	if (index == SETTINGS)
	{
		if (check[0] == 1)
			exit_error("EXIT : [rt_parser_file.c]");
		check[0] = 1;
	}
	else if (index == TEXTURES)
	{
		if (check[1] == 1)
			exit_error("EXIT : [rt_parser_file.c]");
		check[1] = 1;
	}
}
