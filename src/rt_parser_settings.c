#include "parser.h"

static t_parser		*s_init_new_parser(t_parser *new_parser);
static int			s_index_data(char **file, int size);
static void 		s_get_light_var(int index, char *file, t_set *set);

typedef struct		s_data
{
	char			*name;
	int				size;
	void			*(*ft_conv)(char *);
}					t_data;

static const		t_data	tab_data[] = {	{"width=", sizeof(int), &rt_atoi},
											{"height=", sizeof(int), &rt_atoi},
											{"max_reflect", sizeof(int), &rt_atoi},
											{"anti_allias", sizeof(int), &rt_atoi},
											{"ambient", sizeof(int), &rt_atoi},
											{"stereo", sizeof(cl_float), &rt_get_float},
											{"name=", sizeof(char *), &rt_get_str},
											{"}", 0, NULL}	}; // faire FT

t_parser			*rt_parser_settings(char *file, t_parser *parser)
{
	const int		size = sizeof(tab_data) / sizeof(t_data) - 1;
	t_parser		*new_parser;
	int				mask_check;
	int				index;

	mask_check = 0;
	new_parser = s_init_new_parser(new_parser);
	while ((index = s_index_data(&file, size)) != size)
	{
		rt_add_mask(&mask_check, index);
		s_get_light_var(index, file, (t_set *)new_parser->content);
		file = rt_goto_data_end(file - 1);
	}
	parser->next = new_parser;
	parser = parser->next;
	return (parser);
}

static t_parser		*s_init_new_parser(t_parser *new_parser)
{
	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->content = (t_set *)rt_memalloc(sizeof(t_set));
	new_parser->elem = SETTINGS;
	new_parser->next = NULL;
	return (new_parser);
}

static int			s_index_data(char **file, int size)
{
	int				i;

	i = 0;
	size += 1;
	while (i < size)
	{
		if (rt_strcmp(tab_data[i].name, *file) == 0)
		{
			*file += ft_strlen(tab_data[i].name);
			return (1);
		}
		++i;
	}
	return (_(exit_error("EXIT : s_choice_data [rt_parser_light]"), false));
}

static void 		s_get_light_var(int index, char *file, t_set *set)
{
	void			*var;
	int				i;
	int				offset;

	var = tab_data[index].ft_conv(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += tab_data[i].size;
		++i;
	}
	ft_memcpy((char *)set + offset, var, tab_data[index].size);
}
