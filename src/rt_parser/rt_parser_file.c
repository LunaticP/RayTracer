#include "parser.h"

static t_parser			*s_init_parser(void);
static t_set			*s_init_settings(void);
static int				s_choice_lvl_1(char **file, int size);

typedef struct		s_type_elem
{
	char			*name;
	t_parser		*(*ft_elem)();
}					t_type_elem;

static const t_type_elem tab_elem[] = {	{"objects{", &rt_parser_objects},
										{"lights{", &rt_parser_lights},
										{"camera{", &rt_parser_camera},
										{"settings{", NULL},
										{"}", NULL}		};

t_parser				*rt_parser_file(char *file)
{
	t_parser	*parser;
	t_parser	*ptr_parser;
	int			index;
	int			size;

	parser = s_init_parser();
	ptr_parser = parser;
	size = sizeof(tab_elem) / sizeof(char *) - 1;
	while ((index = s_choice_lvl_1(&file, size)) != size)
	{
		ptr_parser = tab_elem[index].ft_elem(file, ptr_parser);
		file = rt_goto_bracket_close(file);
	}
	return (parser);
}

static t_parser			*s_init_parser(void)
{
	t_parser	*parser;

	parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	parser->content = (t_set *)s_init_settings();
	parser->elem = SETTINGS;
	parser->next = NULL;
	return (parser);
}

static t_set			*s_init_settings(void)
{
	t_set		*settings;

	settings = (t_set *)rt_memalloc(sizeof(t_set));
	settings->name = "Default";
	settings->width = 900;
	settings->height = 700;
	settings->max_reflect = 2;
	settings->anti_allias = 2;
	return (settings);
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
	exit_error("EXIT : rt_choice_lvl_1");
	return (-1);
}
