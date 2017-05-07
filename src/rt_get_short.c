#include "parser.h"

void			*rt_get_short(char *file)
{
	static void	*c;

	c = rt_atoi(file);
	return (c);
}
