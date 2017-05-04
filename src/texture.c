/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <aviau@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:28:35 by aviau             #+#    #+#             */
/*   Updated: 2017/05/03 12:18:32 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <rt.h>

void	disp_perc(int i, int p)
{
	ft_putstr("   \e[u\e[K\e[33m");
	ft_putnbr(i);
	ft_putstr(" \e[0m/ \e[32m");
	ft_putnbr(p);
	ft_putstr("\e[0m\t[\e[36m");
	ft_putnbr(i * 100 / p);
	ft_putstr("%\e[0m]");
}

void	init_ppm(int fd, int **ppm, int *size, char *file)
{
	char	*line;
	int		i;

	if (fd > 0 && get_next_line(fd, &line) && !ft_strcmp(line, (char *)"P3"))
		ft_putstr(file);
	else
		exit(1);
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
	*ppm = ft_memalloc(sizeof(int) * (size[0] * size[1] + 3));
	(*ppm)[0] = size[0] * size[1] + 3;
	(*ppm)[1] = size[0];
	(*ppm)[2] = size[1];
	free(line);
}

int		*get_ppm(char *file)
{
	int		fd;
	int		*ppm;
	char	*line;
	int		size[3];
	int		ij[2];

	line = NULL;
	fd = open(file, O_RDONLY);
	init_ppm(fd, &ppm, size, file);
	ij[0] = 3;
	ij[1] = 0;
	get_next_line(fd, &line);
	while (ij[0] <= ppm[0])
	{
		ij[1] = -1;
		while (++ij[1] <= 2 && get_next_line(fd, &line))
			size[ij[1]] = ft_atoi(line);
		ppm[ij[0]] = size[0] * 0x10000 + size[1] * 0x100 + size[2];
		if ((++ij[0] % 100) == 0 || ij[0] == ppm[0])
			disp_perc(ij[0], ppm[0]);
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

	i = -1;
	len = src[0] + dst[0] - 1;
	out = ft_memalloc(sizeof(int) * len);
	while (++i < src[0])
		out[i] = src[i];
	while (i < len)
	{
		out[i] = dst[i - src[0] + 1];
		i++;
	}
	out[0] = len;
	return (out);
}

int		*get_texture(char **files)
{
	int i;
	int *out;

	if (files == NULL)
		return (0);
	i = 1;
	out = get_ppm(files[0]);
	while (files[i] != '\0')
	{
		out = int_join(out, get_ppm(files[i]));
		i++;
	}
	return (out);
}
