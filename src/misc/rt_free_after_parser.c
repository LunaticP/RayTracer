#include "parser.h"

static void				s_free_file(char *file);
static void				s_free_parser(t_parser *parser);

void				rt_free_after_parser(char *file, t_parser *parser)
{
	s_free_file(file);
	s_free_parser(parser);
}

static void				s_free_file(char *file)
{
	ft_strdel(&file);
}

static void				s_free_parser(t_parser *parser)
{
	t_parser			*parser_ptr;

	parser_ptr = parser;
	while (parser)
	{
		parser_ptr = parser;
		free(parser->content);
		parser = parser->next;
		free(parser_ptr);
	}
}
