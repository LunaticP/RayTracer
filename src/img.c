/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:45:24 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/22 23:02:27 by jogarcia         ###   ########.fr       */
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

void	img_file(t_mlx *mlx)
{
	time_t	t;
	char	*name[2];
	int		fd;
	int		pos[2];

	t = time(NULL);
	name[0] = ft_strjoin(ft_stroccur(ctime(&t), ' ', '_'), "_rt.ppm");
	fd = open(name[0], O_CREAT | O_TRUNC | O_WRONLY, 0775);
	ft_putstr_fd("P6\n", fd);
	ft_putstr_fd(name[1] = ft_itoa(mlx->W), fd);
	ft_strdel(&name[1]);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(name[1] = ft_itoa(mlx->H), fd);
	ft_strdel(&name[1]);
	ft_putstr_fd("\n255\n", fd);
	pos[1] = -1;
	while (++pos[1] < mlx->H && (pos[0] = -1))
		while (++pos[0] < mlx->W)
		{
			write(fd, &(mlx->p[(pos[1] * mlx->WIDTH + pos[0]) * 4 + 2]), 1);
			write(fd, &(mlx->p[(pos[1] * mlx->WIDTH + pos[0]) * 4 + 1]), 1);
			write(fd, &(mlx->p[(pos[1] * mlx->WIDTH + pos[0]) * 4]), 1);
		}
	close(fd);
	ft_putendl("File Rendered.");
}
