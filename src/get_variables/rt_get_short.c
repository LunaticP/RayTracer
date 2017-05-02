#include "parser.h"

void			*rt_get_short(char *file)
{
	static short	c;

	c = atoi(file);
	return ((void *)&c);
}
