#include "parser.h"

void			*rt_get_str(char *file)
{
	int			i;

	i = 0;
	++file;
	while (file[i] && file[i] != '"')
		++i;
	if (file[i] != ';')
		exit_error("EXIT : [rt_get_str.c]");
	return (ft_memcpy(ft_strnew(i), file, i));
}
