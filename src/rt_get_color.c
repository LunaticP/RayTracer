#include "parser.h"
static int		s_check_color(char *file);
static int		s_check_hexa(char c);

void			*rt_get_color(char *file)
{
	static cl_int	color;

	color = 0;
	if (s_check_color(file) == 0)
		exit_error("EXIT : rt_get_color");
	++file;
	while (*file != ';')
	{
		color *= 16;
		if ('0' <= *file && *file <= '9')
			color += (*file - '0');
		else if ('a' <= *file && *file <= 'f')
			color += (*file - 'a') + 10;
		else if ('A' <= *file && *file <= 'F')
			color += (*file - 'A') + 10;
		++file;
	}
	return ((void *)&color);
}

static int		s_check_color(char *file)
{
	int		i;

	i = 0;
	if (file[i] == '#')
	{
		++i;
		while (i < 7 && s_check_hexa(file[i]))
			++i;
		if (i == 7 && file[i] == ';')
			return (1);
	}
	return (0);
}

static int		s_check_hexa(char c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))
		return (1);
	return (0);
}