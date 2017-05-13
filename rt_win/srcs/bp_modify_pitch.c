/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp_modify_pitch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:13:37 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/09 20:02:00 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bp_modify_pitch(int id, int keycode, void *data)
{
	t_fslider	*slider;

	slider = *((t_fslider**)data);
	if ((keycode == L_CLICK || keycode == SCROLL_UP) &&
									slider->max * PITCH_SCALE < FTOA_MAX_VALUE)
	{
		slider->max *= PITCH_SCALE;
		*slider->value *= PITCH_SCALE;
	}
	else if ((keycode == R_CLICK || keycode == SCROLL_DOWN) && 
												slider->max / PITCH_SCALE > 0.9)
	{
		slider->max /= PITCH_SCALE;
		*slider->value /= PITCH_SCALE;
	}
	return (id);
}