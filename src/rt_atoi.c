#include "parser.h"

int		rt_atoi(const char *str)
{
	int out;
	int is_negative;

	out = 0;
	while (*str > '\0' && *str <= ' ')
		str++;
	is_negative = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		out *= 10;
		out += (*str - '0');
		str++;
	}
	if (is_negative)
		out = -out;
	if (*str != ';')
		exit_error("EXIT : [rt_atoi.c]");
	return (out);
}
