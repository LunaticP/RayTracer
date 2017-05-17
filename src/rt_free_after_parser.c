/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_after_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 05:07:32 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 05:07:34 by jogarcia         ###   ########.fr       */
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
		free(parser->content);
		parser = parser->next;
		free(parser_ptr);
	}
}
