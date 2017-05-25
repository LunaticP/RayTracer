/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 08:59:00 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 18:34:34 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		rt_fclose(void *data)
{
	float	*tmp;

	if (rt_win_getpitch((int)data, &tmp) < 0)
		return (rt_win_error(__func__, -1));
	return (0);
}
