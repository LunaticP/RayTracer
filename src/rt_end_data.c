/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_end_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:23:35 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:23:38 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char			*rt_goto_data_end(char *file)
{
	if (*file == '{')
		return (rt_goto_bracket_close(file));
	while (*file != ';')
		++file;
	++file;
	return (file);
}
