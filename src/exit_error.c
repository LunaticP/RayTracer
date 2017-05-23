#include "parser.h"
#include <rt.h>

void			exit_error(char *str)
{
	print_error(str);
	exit(0);
}
