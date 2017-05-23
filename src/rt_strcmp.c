#include "parser.h"

int			rt_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1)
		return (-1);
	return (0);
}
