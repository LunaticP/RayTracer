/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:22:51 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:22:52 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int s_check_path(char *path);

AN1;

void				parser_error(t_list *file, char *path)
{
	if (file == NULL || file->content == NULL)
		exit_error("error - parser - get_file send NULL");
	if (s_check_path(path) == -1)
		exit_error("error - parser - bad ext");
}

static int			s_check_path(char *path)
{
	path += ft_strlen(path);
	if (*(path - 1) != 't' || *(path - 2) != 'r' || *(path - 3) != '.')
		return (-1);
	return (1);
}
