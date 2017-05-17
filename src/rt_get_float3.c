/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_float3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 12:08:46 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 12:08:47 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN1 static int rt_get_pos_choice(char **file, int size);

AN1;

static const char	*g_tab_data[] = {
	"x=",
	"y=",
	"z=",
	"}"
};

void					*rt_get_float3(char *file)
{
	static cl_float4	pos;
	const int			size = sizeof(g_tab_data) / sizeof(char *) - 1;
	int					index;
	char				check[3];

	memset(&check, 0, sizeof(char) * 3);
	memset(&pos, 0, sizeof(cl_float4));
	while ((index = rt_get_pos_choice(&file, size)) != size)
	{
		if (0 <= index && index <= 2)
		{
			pos.s[index] = *(float *)rt_get_float(file);
			check[index]++;
			file = rt_next_float(file);
		}
		else
			exit_error("EXIT SECURE : rt_get_float3");
	}
	if (*file != '}' || check[0] != 1 || check[1] != 1 || check[2] != 1)
		exit_error("EXIT : rt_get_float3");
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
	return (_(exit_error("EXIT : rt_get_pos_choice [float3]"), false));
}
