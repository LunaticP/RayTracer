#include "parser.h"

static int				s_choice_lvl_1(char **file, int size);
t_parser				*s_init_settings(char *file, t_parser *parser);

typedef struct		s_type_elem
{
	char			*name;
	t_parser		*(*ft_elem)();
}					t_type_elem;

static const t_type_elem tab_elem[] = {	{"objects{", &rt_parser_objects},
										{"lights{", &rt_parser_lights},
										{"camera{", &rt_parser_camera},
										{"settings{", &rt_parser_settings},
										{"textures{", &rt_parser_textures},
										{"}", NULL}		};

t_parser				*rt_parser_file(char *file)
{
	t_parser	*parser;
	t_parser	*ptr_parser;
	int			index;
	int			size;
	int			check[2];

	check[0] = 0;
	check[1] = 0;
	parser = (t_parser *)rt_memalloc(sizeof(t_parser)); // SURE ? [little tricks]
	ptr_parser = parser;
	size = sizeof(tab_elem) / sizeof(t_type_elem) - 1;
	while ((index = s_choice_lvl_1(&file, size)) != size)
	{
		if (index == SETTINGS)
		{
			if (check[0] == 1)
				exit_error("EXIT : [rt_parser_file.c]");
			check[0] = 1;
		 	// file = rt_goto_bracket_close(file);
		}
		if (index == TEXTURES)
		{
			if (check[1] == 1)
				exit_error("EXIT : [rt_parser_file.c]");
			check[1] = 1;
		}
		ptr_parser = tab_elem[index].ft_elem(file, ptr_parser);
		file = rt_goto_bracket_close(file);
	}
	if (check[0] != 1)
		ptr_parser = s_init_settings(file, ptr_parser);
	return (parser);
}

static int				s_choice_lvl_1(char **file, int size)
{
	int			i;

	i = 0;
	if (**file == '\0')
		return (size);
	while (i < size)
	{
		if (rt_strcmp(tab_elem[i].name, *file) == 0)
		{
			*file += ft_strlen(tab_elem[i].name);
			return (i);
		}
		++i;
	}
	return (_(exit_error("EXIT : rt_choice_lvl_1"), false));
}

t_parser			*s_init_settings(char *file, t_parser *parser)
{
	t_parser		*new_parser;
	t_set			*set;

	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->elem = SETTINGS;
	new_parser->next = NULL;
	set = (t_set *)rt_memalloc(sizeof(t_parser));
	set->width = WIDTH;
	set->height = HEIGHT;
	set->max_reflect = 20;
	set->anti_allias = 1;
	set->ambient = 10;
	set->stereo = 0;
	set->name = "Auto Initialisation";
	new_parser->content = set;
	parser->next = new_parser;
	parser = parser->next;
	return (new_parser);
}
