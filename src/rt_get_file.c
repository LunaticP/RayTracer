#include "parser.h"

static char			*s_file_nospace(char *f);
static int				rt_isspace(char c);

char			*rt_get_file(char *path)
{
	int			fd;
	char		*file;
	char		*line;


	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	file = ft_strnew(0);
	while (0 < get_next_line(fd, &line))
		file = ft_strjoin(file, line);
	file = s_file_nospace(file);
	close(fd);
	return (file);
}

static char			*s_file_nospace(char *file)
{
	char		*file_ns;
	char		*ptr;
	bool		check_str;

	file_ns = (char *)rt_memalloc(ft_strlen(file) + 1);
	ptr = file_ns;
	check_str = 0;
	while (*file)
	{
		if (*file == '"')
			check_str += -1;
		if (rt_isspace(*file) == 0 || check_str == 1)
		{
			*ptr = *file;
			++ptr;
		}
		++file;
	}
	return (file_ns);
}

static int				rt_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
	|| c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);		
}
