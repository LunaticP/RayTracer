/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:49:33 by aviau             #+#    #+#             */
/*   Updated: 2017/05/21 21:00:44 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#define XM mlx->s.cam.size.x
#define YM mlx->s.cam.size.y

void	dsr(t_mlx *mlx)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	cl_int2			p;
	cl_int2			d;

	p.y = -DSR;
	while ((p.y += DSR) + 1 < YM && (p.x = -DSR))
		while ((p.x += DSR) + 1 < XM && (d.y = -1))
		{
			r = 0;
			g = 0;
			b = 0;
			while (++d.y < DSR && (d.x = -1))
				while (++d.x < DSR)
				{
					r += mlx->p[((p.y + d.y) * XM + (p.x + d.x)) * 4 + 2];
					g += mlx->p[((p.y + d.y) * XM + (p.x + d.x)) * 4 + 1];
					b += mlx->p[((p.y + d.y) * XM + (p.x + d.x)) * 4 + 0];
				}
			mlx->p[(p.y / DSR * XM + p.x / DSR) * 4 + 0] = b / (DSR * DSR);
			mlx->p[(p.y / DSR * XM + p.x / DSR) * 4 + 1] = g / (DSR * DSR);
			mlx->p[(p.y / DSR * XM + p.x / DSR) * 4 + 2] = r / (DSR * DSR);
			mlx->p[(p.y / DSR * XM + p.x / DSR) * 4 + 3] = 0;
		}
}
