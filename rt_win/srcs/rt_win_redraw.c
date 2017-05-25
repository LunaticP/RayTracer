/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win_redraw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 21:09:18 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 21:20:48 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

void	rt_win_redraw(int *key)
{
	static int	*redraw;

	redraw = (redraw ? redraw : key);
	*redraw |= 0x00200000;
}
