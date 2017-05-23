#include "parser.h"

#define AN1 static t_parser *s_init_new_parser(t_parser *new_parser);
#define AN2 static char *s_get_path(char *file);
#define AN3 static char **s_exception(char *file, char **path)
#define AN4 static void s_move_next_path(char **file);

AN1;
AN2;
AN3;
AN4;

t_parser				*rt_parser_textures(char *file, t_parser *parser)
{
	t_parser			*new_parser;
	char				*path;

	while (*file != '}')
	{
		if (*file != '"')
			exit_error("[rt_parser_textures.c]");
		new_parser = s_init_new_parser(new_parser);
		path = s_get_path(file);
		new_parser->content = path;
		parser->next = new_parser;
		parser = parser->next;
		s_move_next_path(&file);
	}
	return (parser);
}

static t_parser			*s_init_new_parser(t_parser *new_parser)
{
	new_parser = (t_parser *)rt_memalloc(sizeof(t_parser));
	new_parser->elem = TEXTURES;
	new_parser->next = NULL;
	return (new_parser);
}

static char				*s_get_path(char *file)
{
	int					i;
	char				**path;

	file++;
	path = NULL;
	if ((path = s_exception(file, path)))
		return ((char *)path);
	i = 0;
	while (file[i] != '\0' && file[i] != '"')
		i++;
	if (file[i] == '\0')
		exit_error("s_get_path [rt_parser_textures.c]");
	path = (char **)rt_memalloc(sizeof(char *));
	*path = (char *)rt_memalloc(sizeof(char *) * i + 1);
	ft_memcpy(*path, file, i);
	return ((char *)path);
}

static char				**s_exception(char *file, char **path)
{
	if (rt_strcmp("perlin", file) == 0)
	{
		path = (char **)rt_memalloc(sizeof(char *));
		*path = ft_strdup("perlin");
		return ((char **)path);
	}
	if (rt_strcmp(file, "langton") == 0)
	{
		path = (char **)rt_memalloc(sizeof(char *));
		*path = ft_strdup("langton");
		return ((char **)path);
	}
	return (NULL);
}

static void				s_move_next_path(char **file)
{
	if (**file == '"')
		(*file)++;
	else
		exit_error("s_next_data (1) [rt_parser_textures.c]");
	while (**file != '"')
		(*file)++;
	(*file)++;
	if (**file == ';')
		(*file)++;
	else
		exit_error("s_next_data (2) [rt_parser_textures.c]");
}
