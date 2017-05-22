/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_inside_data_button.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 12:50:23 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/13 08:02:08 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

int		mmlx_inside_data_button(t_mmlx *mlx, void *pixel)
{
	if ((size_t)mlx->data_button <= (size_t)pixel && (size_t)mlx->data_button
			+ (size_t)mlx->ywin * (size_t)mlx->sizeline > (size_t)pixel)
		return (1);
	return (0);
}
