/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   langton.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 13:13:41 by aviau             #+#    #+#             */
/*   Updated: 2017/05/24 00:48:50 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <rt.h>

cl_int2	gen_pos(void)
{
	struct timeval	time;
	cl_int2			pos;

	gettimeofday(&time, NULL);
	srandom((time.tv_sec + time.tv_usec) / 2);
	pos.x = random() % 2048;
	pos.y = random() % 2048;
	return (pos);
}

void	rot_ant(t_ant *ant, unsigned char tile)
{
	if (tile == 0)
	{
		if (ant->dir.x == 0 && ant->dir.y == -1)
			ant->dir = (cl_int2){.x = -1, .y = 0};
		else if (ant->dir.x == -1 && ant->dir.y == 0)
			ant->dir = (cl_int2){.x = 0, .y = 1};
		else if (ant->dir.x == 0 && ant->dir.y == 1)
			ant->dir = (cl_int2){.x = 1, .y = 0};
		else if (ant->dir.x == 1 && ant->dir.y == 0)
			ant->dir = (cl_int2){.x = 0, .y = -1};
	}
	else
	{
		if (ant->dir.x == 0 && ant->dir.y == -1)
			ant->dir = (cl_int2){.x = 1, .y = 0};
		else if (ant->dir.x == 1 && ant->dir.y == 0)
			ant->dir = (cl_int2){.x = 0, .y = 1};
		else if (ant->dir.x == 0 && ant->dir.y == 1)
			ant->dir = (cl_int2){.x = -1, .y = 0};
		else if (ant->dir.x == -1 && ant->dir.y == 0)
			ant->dir = (cl_int2){.x = 0, .y = -1};
	}
}

void	move_ant(t_ant *ant)
{
	ant->pos.x += ant->dir.x;
	ant->pos.y += ant->dir.y;
	(ant->pos.x > 2048) ? ant->pos.x = 0 : 0;
	(ant->pos.y > 2047) ? ant->pos.y = 0 : 0;
	(ant->pos.x < 0) ? ant->pos.x = 2048 : 0;
	(ant->pos.y < 0) ? ant->pos.y = 2047 : 0;
}

void	gen_ant(long iter, int *tex, t_ant ant, unsigned char *map)
{
	long	i;
	int		pos;
	int		col;

	i = -1;
	ant.pos = gen_pos();
	ant.dir.x = 0;
	ant.dir.y = -1;
	while (++i < iter)
	{
		pos = ant.pos.y * 2048 + ant.pos.x;
		col = tex[pos + 3];
		col = (((col & 0xFF0000) / 0x10000) + ant.r) > 255 ?
			col + (ant.r - 255) * 0x10000 : col + ant.r * 0x10000;
		col = (((col & 0xFF00) / 0x100) + ant.g) > 255 ?
			col + (ant.g - 255) * 0x100 : col + ant.g * 0x100;
		col = ((col & 0xFF) + ant.b) > 255 ?
			col + (ant.b - 255) : col + ant.b;
		tex[pos + 3] = col;
		map[pos] = (map[pos] == 0) ? 1 : 0;
		rot_ant(&ant, map[pos]);
		move_ant(&ant);
	}
}

int		*langton(void)
{
	unsigned char	*map;
	int				*tex;
	int				x;
	int				y;

	tex = (int *)ft_memalloc(sizeof(int) * (2048 * 2048 + 3));
	map = (unsigned char *)ft_memalloc(2049 * 2049);
	tex[0] = 2048 * 2048 + 3;
	tex[1] = 2048;
	tex[2] = 2048;
	y = -1;
	while (++y < 2048 && (x = -1))
		while (++x < 2048)
			tex[y * 2048 + x + 3] = 0;
	gen_ant(10000000, tex, (t_ant){.r = 5, .g = 5, .b = 10}, map);
	gen_ant(1000000, tex, (t_ant){.r = 10, .g = 10, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 10, .g = 5, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 5, .g = 10, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 0, .g = 5, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 5, .g = 0, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 0, .g = 0, .b = 5}, map);
	printf("map : %p\n", &map);
	ft_memdel((void **)&map);
	return (tex);
}
