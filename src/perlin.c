/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:57:35 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/24 01:46:35 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <rt.h>

unsigned char	*gen_image(int xx, int yy)
{
	unsigned char	*image;
	struct timeval	time;
	int				x;
	int				y;

	gettimeofday(&time, NULL);
	srandom((time.tv_sec + time.tv_usec) / 2);
	image = (unsigned char *)ft_memalloc(xx * yy);
	y = -1;
	while (++y < yy && (x = -1))
		while (++x < xx)
			image[y * xx + x] = (random() % 32768) / 32768.0 * 255.0;
	return (image);
}

float			smooth(float x, float y, int m, unsigned char *map)
{
	cl_float2	fct;
	cl_int2		fst;
	cl_int2		snd;
	float		value;

	fct.x = x - (int)x;
	fct.y = y - (int)y;
	value = 0.0;
	fst.x = (int)x % m;
	fst.y = (int)y % m;
	snd.x = ((int)x + m - 1) % m;
	snd.y = ((int)y + m - 1) % m;
	value += fct.x * fct.y * (map[fst.y * m + fst.x] / 255.0);
	value += (1.0 - fct.x) * fct.y * (map[fst.y * m + snd.x] / 255.0);
	value += fct.x * (1.0 - fct.y) * (map[snd.y * m + fst.x] / 255.0);
	value += (1.0 - fct.x) * (1.0 - fct.y) * (map[snd.y * m + snd.x] / 255.0);
	return (value);
}

int				merge(unsigned char **images, int x, int y)
{
	float	div;
	float	val;
	int		i;

	i = 0;
	div = 1.0;
	val = (int)(smooth(x, y, 2048, images[0]) * 255.0);
	while (++i < 7)
	{
		div *= 2.0;
		val += (smooth(x / div, y / div, 2048 / div, images[i]) * 255.0);
	}
	val /= 8.0;
	return ((int)val * 0x10000 + (int)val * 0x100 + (int)val);
}

int				*perlin(void)
{
	unsigned char	*img[8];
	int				*tex;
	cl_int2			p;

	tex = (int *)ft_memalloc(sizeof(int) * 2048 * 2048 + 3);
	tex[0] = 2048 * 2048 + 3;
	tex[1] = 2048;
	tex[2] = 2048;
	img[0] = gen_image(2048, 2048);
	img[1] = gen_image(1024, 1024);
	img[2] = gen_image(512, 512);
	img[3] = gen_image(256, 256);
	img[4] = gen_image(128, 128);
	img[5] = gen_image(64, 64);
	img[6] = gen_image(32, 32);
	img[7] = gen_image(16, 16);
	p.y = -1;
	while (++p.y < 2048)
	{
		p.x = -1;
		while (++p.x < 2048)
			tex[p.y * 2048 + p.x + 3] = merge((unsigned char **)img, p.x, p.y);
	}
	return (tex);
}
