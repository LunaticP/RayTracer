/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_inside_data_button.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 12:50:23 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/13 08:02:08 by jogarcia         ###   ########.fr       */
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
