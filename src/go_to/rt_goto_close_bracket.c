#include "parser.h"

char			*rt_goto_bracket_close(char *file)
{
	int			check;

	check = 1;
	if (*file == '{')
		++file;
	while (*file && check > 0)
	{
		if (*file == '{')
			++check;
		if (*file == '}')
			--check;
		++file;
	}
	return (file);
}
