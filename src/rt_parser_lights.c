#include "parser.h"

# define MASK_LIGHT		0b0000000000100000100000001

typedef struct		s_data
{
	char 	*name;
	int		size;
	void	*(*ft_conv)(char *);
}					t_data;

static const t_data tab_data[] = {{"pos{", sizeof(cl_float4), &rt_get_float4},
									{"dir{", sizeof(cl_float4), &rt_get_float3},
									{"tet=", sizeof(cl_float), &rt_get_float},
									{"phi=", sizeof(cl_float), &rt_get_float},
									{"rot=", sizeof(cl_float), &rt_get_float},
									{"PADDING", 4, &rt_useless},
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
									{"}", 0, NULL}	};

static t_parser		*s_init_new_parser(t_parser *new_parser);
static int			s_choice_data(char **file, int size);
static void			s_get_light_var(int index, char *file, t_obj *obj);

t_parser			*rt_parser_lights(char *file, t_parser *parser)
{
	t_parser		*new_parser;
	int				mask_check;
	int				index;
	const int		size = sizeof(tab_data) / sizeof(t_data) - 1;

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
		if (rt_strcmp(tab_data[i].name, *file) == 0)
		{
			*file += ft_strlen(tab_data[i].name);
			return (i);
		}
		++i;
	}
	exit_error("EXIT : s_choice_data [rt_parser_light]");
	return (0);
}

static void			s_get_light_var(int index, char *file, t_obj *obj)
{
	void	*var;
	int		i;
	int		offset;

	var = tab_data[index].ft_conv(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += tab_data[i].size;
		++i;
	}
	ft_memcpy((char *)obj + offset, var, tab_data[index].size);
}
