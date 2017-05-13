#include "parser.h"

void			*rt_get_str(char *file)
{
	int					i;
	char				**path;

	file++;
	i = 0;
	while (file[i] != '\0' && file[i] != '"')
		i++;
	if (file[i] == '\0')
		exit_error("s_get_path [rt_parser_textures.c]");
	path = (char **)rt_memalloc(sizeof(char *));
	*path = (char *)rt_memalloc(sizeof(char *) * i + 1);
	// path = (char **)rt_memalloc(sizeof(char) * i + sizeof(char *));
	// *path = (char *)path + 8;
	ft_memcpy(*path, file, i);
	return ((char *)path);
}
