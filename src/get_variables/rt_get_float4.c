#include "parser.h"

static int				rt_get_pos_choice(char **file, int size);

static const char	*tab_data[] = {	"x=",
									"y=",
									"z=",
									"w=",
									"}" };

void		*rt_get_float4(char *file)
{
	static cl_float4	pos;
	const int			size = sizeof(tab_data) / sizeof(char *) - 1;
	int			index;
	char		check[4];

	memset(&check, 0, sizeof(char) * 4);
	memset(&pos, 0, sizeof(cl_float4));
	while ((index = rt_get_pos_choice(&file, size)) != size)
	{
		if (0 <= index && index <= 3)
		{
			pos.s[index] = *(float *)rt_get_float(file);
			check[index]++;
			file = rt_next_float(file);
		}
		else
			exit_error("EXIT SECURE : rt_get_float4");
	}
	if (*file != '}' || check[0] != 1 || check[1] != 1 || check[2] != 1 || check[3] != 1)
		exit_error("EXIT : rt_get_float4");
	return ((void *)&pos);
}

static int				rt_get_pos_choice(char **file, int size)
{
	int			i;

	i = 0;
	while (i <= size)
	{
		if (rt_strcmp(tab_data[i], *file) == 0)
		{
			if (**file == '}')
				return (i);
			*file += ft_strlen(tab_data[i]);
			return (i);
		}
		++i;
	}
	return (exit_error("EXIT : rt_get_pos_choice [float4]"), false);
}
