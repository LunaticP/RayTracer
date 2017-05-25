/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_onslider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 00:46:24 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/06 04:44:37 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_onslider(t_slideon *sldr, int x, int y)
{
	if (sldr->pos_x <= x && x < sldr->pos_x + sldr->data.slider_sizex &&
		sldr->pos_y <= y && y < sldr->pos_y + sldr->data.slider_sizey)
		return (1);
	else if (sldr->pos_x + sldr->cursor_pos_x <= x
		&& x < sldr->pos_x + sldr->cursor_pos_x + sldr->data.cursor_sizex
		&& sldr->pos_y + sldr->cursor_pos_y <= y
		&& y < sldr->pos_y + sldr->cursor_pos_y + sldr->data.cursor_sizey)
		return (1);
	return (0);
}
