/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:23:18 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:23:21 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN0 static int s_check_textures_limites(short check, int max);
#define AN1 static int s_check_01(cl_float var_test);

AN0;
AN1;

void			rt_check_value(void ***tab, int *tab_size)
{
	t_obj		*ptr;

	ptr = (t_obj *)tab[0];
	while (ptr->type != end)
	{
		if (s_check_textures_limites(ptr->n_m, tab_size[4])
				|| s_check_textures_limites(ptr->r_m, tab_size[4])
				|| s_check_textures_limites(ptr->t_m, tab_size[4]))
			exit_error("EXIT : [rt_check_value.c] 0");
		if (s_check_01(ptr->diff) || s_check_01(ptr->refl)
				|| s_check_01(ptr->trans))
			exit_error("EXIT : [rt_check_value.c] 1");
		if (!(0 <= ptr->alpha && ptr->alpha <= 180))
			exit_error("EXIT : [rt_check_value.c] 2");
		++ptr;
	}
}

static int		s_check_textures_limites(short check, int max)
{
	if (0 <= check && check <= max)
		return (0);
	return (-1);
}

static int		s_check_01(cl_float var_test)
{
	if (0 <= var_test && var_test <= 1)
		return (0);
	return (-1);
}
