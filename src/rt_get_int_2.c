/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_int_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:26:52 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:26:54 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int rt_get_nb_choice(char **file, int size);
#define AN2 static void s_next_int(char **file);

AN1;
AN2;

static const char *g_tab_data[] = {
	"x=",
	"y=",
	"}"
};

void				*rt_get_int2(char *file)
{
	static cl_int2	nb;
	const int		size = sizeof(g_tab_data) / sizeof(char *) - 1;
	int				index;
	char			check[2];

	memset(&check, 0, sizeof(char) * 2);
	memset(&nb, 0, sizeof(cl_int2));
	while ((index = rt_get_nb_choice(&file, size)) != size)
	{
		if (0 <= index && index <= 1)
		{
			nb.s[index] = atoi(file);
			check[index]++;
			s_next_int(&file);
		}
		else
			exit_error("EXIT SECURE : rt_get_int2");
	}
	if (*file != '}' || check[0] != 1 || check[1] != 1)
		exit_error("EXIT : rt_get_int2");
	return ((void *)&nb);
}

static int			rt_get_nb_choice(char **file, int size)
{
	int				i;

	i = 0;
	while (i <= size)
	{
		if (rt_strcmp(g_tab_data[i], *file) == 0)
		{
			if (**file == '}')
				return (i);
			*file += ft_strlen(g_tab_data[i]);
			return (i);
		}
		++i;
	}
	return (_(exit_error("EXIT : rt_get_nb_choice [int2]"), false));
}

static void			s_next_int(char **file)
{
	while (ft_isdigit(**file))
		++(*file);
	++(*file);
}
