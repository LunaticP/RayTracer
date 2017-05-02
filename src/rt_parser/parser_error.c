#include "parser.h"

static int		s_check_path(char *path);

void			parser_error(t_list *file, char *path)
{
	if (file == NULL || file->content == NULL)
		exit_error("error - parser - get_file send NULL");
	if (s_check_path(path) == -1)
		exit_error("error - parser - bad ext");
}

static int			s_check_path(char *path)
{
	path += ft_strlen(path);
	if (*(path - 1) != 't' || *(path - 2) != 'r' || *(path - 3) != '.')
		return (-1);
	return (1);
}
