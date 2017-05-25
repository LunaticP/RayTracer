/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_float3_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:25:26 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:25:27 by jogarcia         ###   ########.fr       */
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

void					*rt_get_float3_init(char *file)
{
	static cl_float4	pos;
	const int			size = sizeof(g_tab_data) / sizeof(char *) - 1;
	int					index;
	char				check[3];

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
	if (*file != '}')
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
