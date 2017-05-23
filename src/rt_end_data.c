#include "parser.h"

char			*rt_goto_data_end(char *file)
{
	if (*file == '{')
		return (rt_goto_bracket_close(file));
	while (*file != ';')
		++file;
	++file;
	return (file);
}
