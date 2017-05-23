/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_after_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:24:09 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:24:11 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static void				s_free_file(char *file);
#define AN2 static void				s_free_parser(t_parser *parser);

AN1;
AN2;

void					rt_free_after_parser(char *file, t_parser *parser)
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
		if (parser->elem == TEXTURES)
			free(*((char **)(parser->content)));
		free(parser->content);
		parser = parser->next;
		free(parser_ptr);
	}
}
