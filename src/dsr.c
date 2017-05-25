/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:49:33 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 14:58:50 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#define XM mlx->s.cam.size.x
#define YM mlx->s.cam.size.y
#define DSRSQ (mlx->DSR * mlx->DSR)

void	dsr(t_mlx *mlx)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	cl_int2			p;
	cl_int2			d;

	p.y = -mlx->DSR;
	while ((p.y += mlx->DSR) + 1 < YM && (p.x = -mlx->DSR))
		while ((p.x += mlx->DSR) + 1 < XM && (d.y = -1))
		{
			r = 0;
			g = 0;
			b = 0;
			while (++d.y < mlx->DSR && (d.x = -1))
				while (++d.x < mlx->DSR)
				{
					r += mlx->p[((p.y + d.y) * XM + (p.x + d.x)) * 4 + 2];
					g += mlx->p[((p.y + d.y) * XM + (p.x + d.x)) * 4 + 1];
					b += mlx->p[((p.y + d.y) * XM + (p.x + d.x)) * 4 + 0];
				}
			mlx->p[(p.y / mlx->DSR * XM + p.x / mlx->DSR) * 4 + 0] = b / DSRSQ;
			mlx->p[(p.y / mlx->DSR * XM + p.x / mlx->DSR) * 4 + 1] = g / DSRSQ;
			mlx->p[(p.y / mlx->DSR * XM + p.x / mlx->DSR) * 4 + 2] = r / DSRSQ;
			mlx->p[(p.y / mlx->DSR * XM + p.x / mlx->DSR) * 4 + 3] = 0;
		}
}
