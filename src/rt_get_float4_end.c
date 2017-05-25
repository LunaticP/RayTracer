/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_float4_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:25:43 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:25:44 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int rt_get_pos_choice(char **file, int size);

AN1;

static const char	*g_tab_data[] = {
	"z=",
	"w=",
	"}"
};

void					*rt_get_float4_end(char *file)
{
	static cl_float4	pos;
	const int			size = sizeof(g_tab_data) / sizeof(char *) - 1;
	int					index;
	char				check[2];

	memset(&check, 0, sizeof(char) * 2);
	memset(&pos, 0, sizeof(cl_float4));
	while ((index = rt_get_pos_choice(&file, size)) != size)
	{
		if (0 <= index && index <= 1)
		{
			pos.s[index + 2] = *(float *)rt_get_float(file);
			check[index]++;
			file = rt_next_float(file);
		}
		else
			exit_error("EXIT SECURE : rt_get_float4_end");
	}
	if (*file != '}' || check[0] != 1 || check[1] != 1)
		exit_error("EXIT : rt_get_float4_end");
	return ((void *)&pos);
}

static int				rt_get_pos_choice(char **file, int size)
{
	int					i;

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
	return (_(exit_error("EXIT : rt_get_pos_choice [float4_end]"), false));
}
