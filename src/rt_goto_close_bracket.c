/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_goto_close_bracket.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:29:54 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:29:55 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char			*rt_goto_bracket_close(char *file)
{
	int			check;

	check = 1;
	if (*file == '{')
		++file;
	while (*file && check > 0)
	{
		if (*file == '{')
			++check;
		if (*file == '}')
			--check;
		++file;
	}
	return (file);
}
