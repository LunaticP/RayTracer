/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_init_tmlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:18:32 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/18 16:47:27 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_init_tmlx(t_mmlx *x, t_datawin *data)
{
	x->f_keypress = data->f_keypress;
	x->data_kp = data->data_kp;
	x->f_keyrelease = data->f_keyrelease;
	x->data_kr = data->data_kr;
	x->f_close = data->f_close;
	x->data_cl = data->data_cl;
	x->f_loop = data->f_loop;
	x->data_lp = data->data_lp;
	x->f_mousepress = data->f_mousepress;
	x->data_mp = data->data_mp;
	x->f_mouserelease = data->f_mouserelease;
	x->data_mr = data->data_mr;
	x->f_followmouse = data->f_followmouse;
	x->data_fm = data->data_fm;
	ml_memset((void*)x->button_used, 0, sizeof(int) * DFLT_MAX_BUTTONWIN);
	ml_memset((void*)x->string_used, 0, sizeof(int) * DFLT_MAX_STRINGWIN);
	ml_memset((void*)x->slider_used, 0, sizeof(int) * DFLT_MAX_SLIDERWIN);
	ml_memset((void*)x->switch_used, 0, sizeof(int) * DFLT_MAX_SWITCHWIN);
}
