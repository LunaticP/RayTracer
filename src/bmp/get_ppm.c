/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ppm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:15:03 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/13 19:17:08 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_bmp.h>
#include <libft.h>

void	init_ppm(int fd, int **ppm, int *size, char *file)
{
	char	*line;
	int		i;

	if (fd > 0 && get_next_line(fd, &line) && !ft_strcmp(line, (char *)"P3"))
	{
		line = ft_strrchr(file, '/');
		if (line == NULL)
			ft_putstr(file);
		else
			ft_putstr(line + 1);
	}
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
