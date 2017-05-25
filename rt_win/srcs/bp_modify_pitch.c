/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp_modify_pitch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:13:37 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/11 15:31:02 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

int		bp_modify_pitch(int id, int keycode, void *data)
{
	t_fslider	*slider;

	slider = *((t_fslider**)data);
	if ((keycode == L_CLICK || keycode == SCROLL_UP) &&
								slider->max * MOD_PITCH_SCALE < FTOA_MAX_VALUE)
	{
		slider->max *= MOD_PITCH_SCALE;
		*slider->value *= MOD_PITCH_SCALE;
	}
	else if ((keycode == R_CLICK || keycode == SCROLL_DOWN) &&
										slider->max / MOD_PITCH_SCALE > 0.9)
	{
		slider->max /= MOD_PITCH_SCALE;
		*slider->value /= MOD_PITCH_SCALE;
	}
	return (id);
}
