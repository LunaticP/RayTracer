/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_get_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:30:21 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:01:26 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

t_mmlx	*mmlx_get_parent(int id)
{
	static t_mmlx	parent[DFLT_MAX_PARENT];
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
