/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putimg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:06:06 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/10 22:29:35 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rt_network.h>
#include <libft.h>

t_mlx	*save_mlx(int status, t_mlx *mlx)
{
	static t_mlx	*saved = NULL;

	if (status)
		saved = mlx;
	return (saved);
}

void	putimg(t_client *c)
{
	t_mlx	*mlx;

	mlx = save_mlx(0, NULL);
	ft_memcpy((void *)&(mlx->p[c->line * WIDTH]), &(c->buf), c->len);
}
