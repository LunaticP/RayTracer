/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 01:37:00 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 01:37:02 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int			s_choice_type(char **file, int size);
#define AN2 static t_parser		*s_add_object(void);
#define AN3 static t_parser		*s_init_new_parser(void);

AN1;
AN2;
AN3;

#define MASK_PLAN 		0b111100000000001111111000011
#define MASK_SPHERE		0b111100000000101111111000011
#define MASK_CYLINDRE 	0b111100001011101111111000011
#define MASK_CONE		0b111100001111001111111000011
#define MASK_TRIANGLE 	0b111111100000001111111000011

static const t_objects	g_tab_objects[] = {
	{"plan{", MASK_PLAN},
	{"triangle{", MASK_TRIANGLE},
	{"sphere{", MASK_SPHERE},
	{"cylindre{", MASK_CYLINDRE},
	{"cone{", MASK_CONE},
	{"}", 0}
};

t_parser				*rt_parser_objects(char *file, t_parser *ptr_parser)
{
	int					index;
	t_parser			*new_parser;
	int					size;

	size = sizeof(g_tab_objects) / sizeof(t_objects) - 1;
	while ((index = s_choice_type(&file, size)) != size)
	{
		new_parser = s_init_new_parser();
		rt_get_object(new_parser->content, file, g_tab_objects[index].mask);
		((t_obj *)new_parser->content)->type = index;
		ptr_parser->next = new_parser;
		ptr_parser = ptr_parser->next;
		file = rt_goto_bracket_close(file);
	}
	return (ptr_parser);
}

static int				s_choice_type(char **file, int size)
{
	int					i;

	i = 0;
	size += 1;
	while (i < size)
	{
		if (rt_strcmp(g_tab_objects[i].name, *file) == 0)
		{
			*file += ft_strlen(g_tab_objects[i].name);
			return (i);
		}
		++i;
	}
	exit_error("EXIT : s_choice_type [rt_parser_objects]");
	return (-1);
}

static t_parser			*s_init_new_parser(void)
{
	t_parser			*parser;

	parser = s_add_object();
	return (parser);
}

static t_parser			*s_add_object(void)
{
	t_parser	*parser;

	parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	parser->content = (t_obj *)rt_memalloc(sizeof(t_obj));
	parser->elem = OBJECTS;
	parser->next = NULL;
	return (parser);
}
