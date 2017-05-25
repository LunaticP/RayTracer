/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_string_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 06:28:32 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:07:04 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_string_remove(int id, t_mmlx *win)
{
	int		i;

	i = 0;
	if (0 <= id && id < DFLT_MAX_STRINGWIN)
	{
		win->string_used[id] = 0;
		ml_strdel(&win->string_tab[id].string);
	}
	else if (id < 0)
	{
		while (i < DFLT_MAX_STRINGWIN)
		{
			win->string_used[i] = 0;
			i++;
		}
		return (mmlx_error(__func__, STRING_NEGATIVE_ID));
	}
	else
		return (mmlx_error(__func__, STRING_UNUSED_ID));
	return (0);
}
