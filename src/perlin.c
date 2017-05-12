#include <stdlib.h>
#include <time.h>
#include <rt.h>

char	*gen_image(int xx, int yy)
{
	char	*image;
	int		x;
	int		y;

	image = (char *)ft_memalloc(xx * yy);
	y = -1;
	while (++y < yy && (x = -1))
		while (++x < xx)
			image[y * xx + x] = (rand() % 32768) / 32768.0 * 255.0;
	return (image);
}

double	smooth(double x, double y, int m_w, int m_h, char *map)
{
   double fractX = x - (int)x;
   double fractY = y - (int)y;
   int x1 = ((int)x + m_w) % m_w;
   int y1 = ((int)y + m_h) % m_h;
   int x2 = ((x1 + m_w) % m_w) - 1;
   int y2 = ((y1 + m_h) % m_h) - 1;
   double value = 0.0;

   value += fractX * fractY * (map[y1 * m_w + x1] / 256.0);
   value += (1.0 - fractX) * fractY * (map[y1 * m_w + x2] / 256.0);
   value += fractX * (1.0 - fractY) * (map[y2 * m_w + x1] / 256.0);
   value += (1.0 - fractX) * (1.0 - fractY) * (map[y2 * m_w + x2] / 256.0);
   return (1.0 - value);
}

int		merge(char **images, int x, int y)
{
	int		val;
	int		div;
	int		i;
	
	i = 0;
	div = 1;
	val = (int)(smooth(x / 1024, y / 1024, 2, 2, images[10]) * 256.0);
//	val = images[0][y / 8 * 2048 + x / 8];
//	while (++i < 8)
//	{
//		div *= 2;
//		val += images[i][(y / div) * (2048 / div) + (x / div)];
//	}
//	val /= 8;
	return(val * 0x10000 + val * 0x100 + val);
}

int		*perlin(void)
{
	char	*images[11];
	int		*tex;
	cl_int2	p;

	tex = (int *)ft_memalloc(sizeof(int) * 2048 * 2048 + 3);
	tex[0] = 2048 * 2048;
	tex[1] = 2048;
	tex[2] = 2048;
	images[0] = gen_image(2048, 2048);
	images[1] = gen_image(1024, 1024);
	images[2] = gen_image(512, 512);
	images[3] = gen_image(256, 256);
	images[4] = gen_image(128, 128);
	images[5] = gen_image(64, 64);
	images[6] = gen_image(32, 32);
	images[7] = gen_image(16, 16);
	images[8] = gen_image(8, 8);
	images[9] = gen_image(4, 4);
	images[10] = gen_image(2, 2);
	p.y = -1;
	while (++p.y < 2048)
	{
		p.x = -1;
		while (++p.x < 2048)
			tex[p.y * 2048 + p.x + 3] = merge((char **)images, p.x, p.y);
	}
	return (tex);
}
