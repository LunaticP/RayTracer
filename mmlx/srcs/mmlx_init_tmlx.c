/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_init_tmlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:18:32 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/06 00:24:55 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	mmlx_init_tmlx(t_mlx *x)
{
	x->f_keypress = NULL;
	x->data_kp = NULL;
	x->f_mousepress = NULL;
	x->data_mp = NULL;
	x->f_mouserelease = NULL;
	x->data_mr = NULL;
	x->f_followmouse = NULL;
	x->data_fm = NULL;
	ml_memset((void*)x->button_used, 0, sizeof(int) * DFLT_MAX_BUTTONWIN);
	ml_memset((void*)x->string_used, 0, sizeof(int) * DFLT_MAX_STRINGWIN);
	ml_memset((void*)x->slider_used, 0, sizeof(int) * DFLT_MAX_SLIDERWIN);
}
