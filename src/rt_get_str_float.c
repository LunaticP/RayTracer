#include "parser.h"

char			*rt_get_str_float(char *file)
{
	int			i;
	int			check;

	i = 0;
	check = 0;
	if (file[i] == '-')
		++i;
	if (file[i] == ';' || (file[i] == '.' && ft_isdigit(file[i + 1]) == 0))
	{
		ft_putendl("EXIT : rt_get_float [fist case]");
		exit(-1);
	}
	while (ft_isdigit(file[i]) == 1)
		++i;
	if (file[i] == '.')
		++i;
	while (ft_isdigit(file[i]) == 1)
		++i;
	if (file[i] != ';')
	{
		ft_putendl("EXIT : rt_get_float [second case]");
		exit(-1);
	}
	return (ft_strncpy(ft_strnew(i), file, i));
}

char			*rt_next_float(char *file)
{
	while (*file != ';')
		++file;
	++file;
	return (file);
}
