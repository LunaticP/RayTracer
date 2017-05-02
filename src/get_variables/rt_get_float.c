#include "parser.h"

static float		s_get_mentisse(char *str);

void				*rt_get_float(char *str)
{
	static float	full;
	int				neg;

	str = rt_get_str_float(str);
	neg = 1;
	if (*str == '-')
		neg = -1;
	full = ft_atoi(str);
	full += s_get_mentisse(str) * neg;
	return ((void *)&full);
} 

static float		s_get_mentisse(char *str)
{
	float		full;
	float		multiple;

	full = 0;
	multiple = 10;
	while (*str != '.' && *str)
		++str;
	if (*str == '.')
		++str;
	if (*str == '\0')
		return (full);
	while (*str)
	{
		full = full + ((float)(*str - '0') / multiple);
		multiple *= (float)10;
		++str;
	}
	return (full);
}
