#include "parser.h"

# define MASK_CAMERA 0b11111

typedef	struct		s_data_camera
{
	char			*name;
	int				size;
	void			*(*ft_conv)(char *);
}					t_data_camera;

static const t_data_camera tab_data_camera[] = {	{"ori{", sizeof(cl_float4), &rt_get_float3},
													{"dirx{", sizeof(cl_float4), &rt_get_float3},
													{"diry{", sizeof(cl_float4), &rt_get_float3},
													{"dirz{", sizeof(cl_float4), &rt_get_float3},
													{"size{", sizeof(cl_int2), &rt_get_int2},
													{"}", 0, NULL}	};

static int				s_choice_data(char **file, int size);
static void				s_get_camera_var(t_cam *cam, char *file, int index);

t_parser				*rt_parser_camera(char *file, t_parser *parser)
{
	t_parser			*new_parser;
	int					mask_check;
	int					index;
	const int			size = sizeof(tab_data_camera) / sizeof(t_data_camera) - 1;

	mask_check = 0;
	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->content = (t_cam *)rt_memalloc(sizeof(t_cam));
	new_parser->elem = CAMERA;
	new_parser->next = NULL;
	while ((index = s_choice_data(&file, size)) != size)
	{
		rt_add_mask(&mask_check, index);
		s_get_camera_var((t_cam *)new_parser->content, file, index);
		file = rt_goto_data_end(file - 1);
	}
	rt_check_all_data(MASK_CAMERA, mask_check);
	((t_cam *)(new_parser->content))->viewplane.x = 10;
	((t_cam *)(new_parser->content))->viewplane.y = 10.0 * (700.0 / 900.0);
	((t_cam *)(new_parser->content))->p.x = -5;
	((t_cam *)(new_parser->content))->p.y = 5.0 * (700.0 / 900.0);
	((t_cam *)(new_parser->content))->p.z = 5;
	parser->next = new_parser;
	parser = parser->next;
	return (parser);
}

static int		s_choice_data(char **file, int size)
{
	int			i;

	i = 0;
	size += 1;
	while (i < size)
	{
		if (rt_strcmp(tab_data_camera[i].name, *file) == 0)
		{
			*file += ft_strlen(tab_data_camera[i].name);
			return (i);
		}
		++i;
	}
	exit_error("EXIT : s_choice_data [rt_get_camera]");
	return (-1);
}

static void				s_get_camera_var(t_cam *cam, char *file, int index)
{
	void				*var;
	int					i;
	int					offset;

	var = tab_data_camera[index].ft_conv(file);
	i = 0;
	offset = 0;
	while (i < index)
	{
		offset += tab_data_camera[i].size;
		++i;
	}
	memcpy((char *)cam + offset, var, tab_data_camera[index].size);
}
