/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_goto_close_bracket.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 12:18:29 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 12:18:29 by jogarcia         ###   ########.fr       */
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
