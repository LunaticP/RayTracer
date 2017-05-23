/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:26:28 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:26:29 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static char *s_file_nospace(char *f);
#define AN2 static int rt_isspace(char c);

AN1;
AN2;

char					*rt_get_file(char *path)
{
	int					fd;
	char				*file;
	char				*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("EXIT : [get_file.c] WRONG FILE");
	file = ft_strnew(0);
	while (0 < get_next_line(fd, &line))
		file = ft_strjoin_free(file, line, 0);
	file = s_file_nospace(file);
	close(fd);
	return (file);
}

static char				*s_file_nospace(char *file)
{
	char				*file_ns;
	char				*ptr;
	bool				check_str;
	char				*file_free;

	file_free = file;
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
	free(file_free);
	return (file_ns);
}

static int				rt_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
			|| c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
