/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_settings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:33:40 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:33:42 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static t_parser *s_init_new_parser(t_parser *new_parser);
#define AN2 static int s_index_data(char **file, int size);
#define AN3 static void s_get_settings_var(int index, char *file, t_set *set);
#define AN4 static void s_init(t_set *set);

AN1;
AN2;
AN3;
AN4;

static const t_data	g_tab_data[] = {
	{"width=", sizeof(int), &rt_atoi},
	{"height=", sizeof(int), &rt_atoi},
	{"max_reflect=", sizeof(int), &rt_atoi},
	{"}", 0, NULL}
};

t_parser				*rt_parser_settings(char *file, t_parser *parser)
{
	const int			size = sizeof(g_tab_data) / sizeof(t_data) - 1;
	t_parser			*new_parser;
	int					mask_check;
	int					index;

	new_parser = NULL;
	mask_check = 0;
	new_parser = s_init_new_parser(new_parser);
	while ((index = s_index_data(&file, size)) != size)
	{
		s_get_settings_var(index, file, (t_set *)new_parser->content);
		file = rt_goto_data_end(file - 1);
	}
	parser->next = new_parser;
	parser = parser->next;
	return (parser);
}

static t_parser			*s_init_new_parser(t_parser *new_parser)
{
	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->content = (t_set *)rt_memalloc(sizeof(t_set));
	s_init((t_set *)new_parser->content);
	new_parser->elem = SETTINGS;
	new_parser->next = NULL;
	return (new_parser);
}

static int				s_index_data(char **file, int size)
{
	int					i;

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
	return (_(exit_error("EXIT : s_choice_data [rt_parser_settings]"), false));
}

static void				s_get_settings_var(int index, char *file, t_set *set)
{
	void				*var;
	int					i;
	int					offset;

	var = NULL;
	var = g_tab_data[index].ft_conv(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += g_tab_data[i].size;
		++i;
	}
	ft_memcpy((char *)set + offset, var, g_tab_data[index].size);
}

static void				s_init(t_set *set)
{
	set->width = 1280;
	set->height = 720;
	set->max_reflect = 20;
}
