/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fkeypress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 21:34:21 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:51:38 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		rt_fkeypress(int keypress, void *data)
{
	float	*tmp;

	if (keypress == DFLT_EXIT)
		if (rt_win_getpitch((int)data, &tmp) < 0)
			return (rt_win_error(__func__, -1));
	return (0);
}
