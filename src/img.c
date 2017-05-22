/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:45:24 by aviau             #+#    #+#             */
/*   Updated: 2017/05/21 20:46:18 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

char	*ft_stroccur(char *str, char a, char b)
{
	char	*tmp;

	while ((tmp = ft_strchr(str, a)))
		*tmp = b;
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

void	img_file(unsigned char *img)
{
	time_t	t;
	char	*name;
	int		fd;
	int		x;
	int		y;

	t = time(NULL);
	name = ft_strjoin(ft_stroccur(ctime(&t), ' ', '_'), "_rt.ppm");
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0775);
	ft_putstr_fd("P6\n", fd);
	ft_putstr_fd(ft_itoa(W), fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(ft_itoa(H), fd);
	ft_putstr_fd("\n255\n", fd);
	y = -1;
	while (++y < H && (x = -1))
		while (++x < W)
		{
			write(fd, &(img[(y * WIDTH + x) * 4 + 2]), 1);
			write(fd, &(img[(y * WIDTH + x) * 4 + 1]), 1);
			write(fd, &(img[(y * WIDTH + x) * 4]), 1);
		}
	close(fd);
	ft_putendl("File Rendered.");
}
