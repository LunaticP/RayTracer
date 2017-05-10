/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sm_default_flt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:51:34 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/07 20:12:56 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

void	sm_default_flt(float ratiox, float ratioy, void *data)
{
	t_fslider	*slider;

	ratioy = 0;
	slider = (t_fslider*)data;
	*slider->value = (slider->max - slider->min) * ratiox + slider->min;
}
