/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   langton.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 204817/05/13 09:58:21 by aviau             #+#    #+#             */
/*   Updated: 2017/05/13 19:41:34 by aviau            ###   ########.fr       */
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

void	move_ant(t_ant *ant, unsigned char tile)
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
	ant->pos.x += ant->dir.x;
	ant->pos.y += ant->dir.y;
	(ant->pos.x > 2048) ? ant->pos.x = 0 : 0;
	(ant->pos.y > 2048) ? ant->pos.y = 0 : 0;
	(ant->pos.x < 0) ? ant->pos.x = 2048 : 0;
	(ant->pos.y < 0) ? ant->pos.y = 2048 : 0;
//	printf("%2d %2d | %3d %3d\t\t%d\n", ant->dir.x, ant->dir.y, ant->pos.x, ant->pos.y, tile);
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
		col = tex[ant.pos.y * 2048 + ant.pos.x + 3];
		col = (((col & 0xFF0000) / 0x10000) + ant.r) > 255 ?
			col + (ant.r - 255) * 0x10000 : col + ant.r * 0x10000;
		col = (((col & 0xFF00) / 0x100) + ant.g) > 255 ?
			col + (ant.g - 255) * 0x100 : col + ant.g * 0x100;
		col = ((col & 0xFF) + ant.b) > 255 ?
			col + (ant.b - 255) : col + ant.b;
		pos = ant.pos.y * 2048 + ant.pos.x; 
		tex[pos + 3] = col;
		map[pos] = (map[pos] == 0) ? 1 : 0;
		move_ant(&ant, map[pos]);
	}
}
/*
double	smooth(double x, double y, int m_w, int m_h, int *map)
{
   double fractX = x - (int)x;
   double fractY = y - (int)y;
   int x1 = (int)x % m_w;
   int y1 = (int)y % m_h;
   int x2 = ((int)x + m_w - 1) % m_w;
   int y2 = ((int)y + m_h - 1) % m_h;
   double valuer = 0.0;
   double valueg = 0.0;
   double valueb = 0.0;

   valuer += fractX * fractY * (map[y1 * m_w + x1] / 255.0);
   valuer += (1.0 - fractX) * fractY * (map[y1 * m_w + x2] / 255.0);
   valuer += fractX * (1.0 - fractY) * (map[y2 * m_w + x1] / 255.0);
   valuer += (1.0 - fractX) * (1.0 - fractY) * (map[y2 * m_w + x2] / 255.0);
   valueg += fractX * fractY * (map[y1 * m_w + x1] / 255.0);
   valueg += (1.0 - fractX) * fractY * (map[y1 * m_w + x2] / 255.0);
   valueg += fractX * (1.0 - fractY) * (map[y2 * m_w + x1] / 255.0);
   valueg += (1.0 - fractX) * (1.0 - fractY) * (map[y2 * m_w + x2] / 255.0);
   valueb += fractX * fractY * (map[y1 * m_w + x1] / 255.0);
   valueb += (1.0 - fractX) * fractY * (map[y1 * m_w + x2] / 255.0);
   valueb += fractX * (1.0 - fractY) * (map[y2 * m_w + x1] / 255.0);
   valueb += (1.0 - fractX) * (1.0 - fractY) * (map[y2 * m_w + x2] / 255.0);
   return (value);
}

int		merge(unsigned int **images, int x, int y)
{
	float	div;
	int		val;
	int		i;
	
	i = 0;
	div = 1;
	val = (int)(smooth(x, y, 2048, 2048, images[0]) * 255.0);
	while (++i < 8)
	{
		div *= 2.0;
		val += (int)(smooth(x / div, y / div, 2048 / div, 2048/ div, images[i]) * 255.0);
	}
	val /= 11;
	return(val * 0x10000 + val * 0x100 + val);
}
*/
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
	while (++y < 2048)
	{
		x = -1;
		while (++x < 2048)
			tex[y * 2048 + x + 3] = 0;
	}
	gen_ant(10000000, tex, (t_ant){.r = 5, .g = 5, .b = 10}, map);
	gen_ant(1000000, tex, (t_ant){.r = 10, .g = 10, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 10, .g = 5, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 5, .g = 10, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 0, .g = 5, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 5, .g = 0, .b = 5}, map);
	gen_ant(1000000, tex, (t_ant){.r = 0, .g = 0, .b = 5}, map);
	free(map);
	return (tex);
}
