/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <aviau@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:28:35 by aviau             #+#    #+#             */
/*   Updated: 2017/04/07 05:27:53 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <rt.h>

int		*get_ppm(char *file)
{
	int fd;
	int *ppm;
	char *line;
	int size[3];
	int i;
	int j;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd > 0 && get_next_line(fd, &line) && !ft_strcmp(line, (char *)"P3"))
		ft_putstr(file);
	else
		exit (1);
	while (get_next_line(fd, &line) && line[0] == '#')
		free(line);
	size[0] = ft_atoi(line);
	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	size[1] = ft_atoi(&line[i]);
	ft_putstr(" : \e[s");
	ppm = ft_memalloc(sizeof(int) * (size[0] * size[1] + 3));
	ppm[0] = size[0] * size[1] + 3;
	ppm[1] = size[0];
	ppm[2] = size[1];
	i = 3;
	j = 0;
	get_next_line(fd, &line);
	while (i <= ppm[0])
	{
		j = 0;
		while (j <= 2 && get_next_line(fd, &line))
		{
			size[j] = ft_atoi(line);
			j++;
		}
//		ppm[i] = (i % 2) * 255 * 255 * 255 + (i % 4) * 255 * 255 + (i % 3) * 255;
		ppm[i] = size[0] * 0x10000 + size[1] * 0x100 + size[2];
		i++;
		if ((i % 100) == 0 || i == ppm[0])
		{
			ft_putstr("   \e[u\e[K\e[33m");
			ft_putnbr(i);
			ft_putstr(" \e[0m/ \e[32m");
			ft_putnbr(ppm[0]);
			ft_putstr("\e[0m\t[\e[36m");
			ft_putnbr(i * 100 / ppm[0]);
			ft_putstr("%\e[0m]");
		}
	}
	ft_putendl("");
	close(fd);
	return (ppm);
}

int		*int_join(int *src, int *dst)
{
	int *out;
	int	len;
	int	i;

	i = 0;
	len = src[0] + dst[0] - 1;
	out = ft_memalloc(sizeof(int) * len);
	while (i < src[0])
	{
		out[i] = src[i];
//		ft_putnbr(out[i]);
//		ft_putstr(" ");
		i++;
	}
//	ft_putstr("| ");
	while (i < len)
	{
		out[i] = dst[i - src[0] + 1];
//		ft_putnbr(out[i]);
//		ft_putstr(" ");
		i++;
	}
	out[0] = len;
//	ft_putendl("<");
	return (out);
}

int		*get_texture(char **files)
{
	int i;
	int *out;

	i = 1;
	out = get_ppm(files[0]);
	while (files[i] != '\0')
	{
		out = int_join(out, get_ppm(files[i]));
		i++;
	}
	return (out);
}
