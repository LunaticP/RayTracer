/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_onbutton.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 21:24:25 by gsimeon           #+#    #+#             */
/*   Updated: 2017/04/06 17:34:20 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_onbutton(t_clickon *click, int x, int y)
{
	if (click->pos_x <= x && x < click->pos_x + click->data.size_x &&
		click->pos_y <= y && y < click->pos_y + click->data.size_y)
		return (1);
	return (0);
}
