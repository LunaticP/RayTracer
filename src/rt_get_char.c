#include "parser.h"

void		*rt_get_char(char *file)
{
	static char	c;

	c = *file - '0';
	return ((void *)&c);
}
