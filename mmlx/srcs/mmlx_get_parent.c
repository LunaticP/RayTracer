/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_get_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:30:21 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/04 07:56:38 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

t_mlx	*mmlx_get_parent(int id)
{
	static t_mlx	parent[DFLT_MAX_PARENT];
	static int		used[DFLT_MAX_PARENT];
	static int		current_parent;
	int				i;

	i = 0;
	if (id >= 0 && id < DFLT_MAX_PARENT && used[id])
		return (&(parent[id]));
	else if (id >= 0 && id < DFLT_MAX_PARENT)
		return (NULL);
	else
	{
		while (i < DFLT_MAX_PARENT && used[i])
			i++;
		if (i < DFLT_MAX_PARENT)
		{
			current_parent += 1;
			(parent[i]).used = &(used[i]);
			(parent[i]).id = i;
			(parent[i]).count = &current_parent;
			return (&(parent[i]));
		}
		mmlx_error(__func__, MAX_PARENT_ERROR);
		return (NULL);
	}
}
