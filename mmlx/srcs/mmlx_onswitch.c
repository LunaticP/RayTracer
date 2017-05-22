/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_onswitch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 20:57:26 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/11 20:58:28 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_onswitch(t_switchon *click, int x, int y)
{
	if (click->pos_x <= x && x < click->pos_x + click->data.size_x &&
		click->pos_y <= y && y < click->pos_y + click->data.size_y)
		return (1);
	return (0);
}
