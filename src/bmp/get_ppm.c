/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ppm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:15:03 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/15 16:33:47 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_bmp.h>
#include <rt.h>
#include <libft.h>

void	init_ppm(int fd, int **ppm, int *size)
{
	char	*line;
	int		i;

	if (!(fd > 0 && get_next_line(fd, &line) && !ft_strcmp(line, (char *)"P3")))
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
	if (fd < 1)
		exit_error("TEXTURE INVALIDE");
	init_ppm(fd, &ppm, size);
	ij[0] = 3;
	get_next_line(fd, &line);
	while (ij[0] <= ppm[0])
	{
		ij[1] = -1;
		while (++ij[1] <= 2 && get_next_line(fd, &line))
			size[ij[1]] = ft_atoi(line);
		ppm[ij[0]] = size[0] * 0x10000 + size[1] * 0x100 + size[2];
		ij[0]++;
	}
	close(fd);
	return (ppm);
}
