/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_list_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:34:32 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:34:33 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static const int g_tab_data[] = {
	sizeof(t_obj),
	sizeof(t_obj),
	sizeof(t_cam),
	sizeof(t_set),
	sizeof(char **)
};

#define AN1 static void s_tab_size_count(int *tab_size, t_parser *parser);
#define AN2 static void s_tab_alloc(void ****tab, int *tab_size);
#define AN3 static void s_tab_set(void ***tab, t_parser *parser);
#define AN4 static void s_check_texture(void ***tab, int max_textures);

AN1;
AN2;
AN3;
AN4;

void					***rt_list_to_tab(t_parser *parser, int *tab_size)
{
	t_parser			*ptr_parser;
	void				***tab;

	ptr_parser = parser;
	s_tab_size_count(tab_size, ptr_parser);
	s_tab_alloc(&tab, tab_size);
	s_tab_set(tab, ptr_parser);
	s_check_texture(tab, tab_size[4]);
	return (tab);
}

static void				s_tab_size_count(int *tab_size, t_parser *parser)
{
	t_parser			*ptr_parser;

	memset(tab_size, 0, sizeof(int) * SIZE);
	ptr_parser = parser;
	while (ptr_parser)
	{
		++tab_size[ptr_parser->elem];
		ptr_parser = ptr_parser->next;
	}
	++tab_size[TEXTURES];
	++tab_size[OBJECTS];
	++tab_size[LIGHTS];
	if (tab_size[3] > 1 || tab_size[2] != 1)
		exit_error("EXIT : s_tab_count_size [rt_list_to_tab.c]");
}

static void				s_tab_alloc(void ****tab, int *tab_size)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	*tab = rt_memalloc(sizeof(void ***) * SIZE);
	while (i < SIZE)
	{
		(*tab)[i] = rt_memalloc(g_tab_data[i] * tab_size[i]);
		++i;
	}
	if (tab_size[TEXTURES] == 1)
		((t_obj *)((*tab)[TEXTURES]))->type = end;
}

static void				s_tab_set(void ***tab, t_parser *parser)
{
	t_parser			*ptr_parser;
	char				count[SIZE];

	memset(count, 0, sizeof(char) * SIZE);
	ptr_parser = parser;
	while (ptr_parser)
	{
		ft_memcpy((((char **)tab)[ptr_parser->elem])
			+ (g_tab_data[ptr_parser->elem] * count[ptr_parser->elem]),
			ptr_parser->content, g_tab_data[ptr_parser->elem]);
		count[ptr_parser->elem]++;
		ptr_parser = ptr_parser->next;
	}
	((t_obj *)(((char **)tab)[0] + (g_tab_data[0] * count[0])))->type = end;
	((t_obj *)(((char **)tab)[1] + (g_tab_data[1] * count[1])))->type = end;
}

static void				s_check_texture(void ***tab, int max_textures)
{
	int					i;

	i = 0;
	while ((int)((t_obj *)(((t_obj *)tab[0]) + i)->type) != end)
	{
		if ((int)((t_obj *)(((t_obj *)tab[0]) + i))->tex
				> max_textures - 1)
			exit_error("EXIT : Bad Textures in entry data");
		++i;
	}
}
