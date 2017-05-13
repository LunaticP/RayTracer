/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <aviau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:28:35 by aviau             #+#    #+#             */
/*   Updated: 2017/05/13 19:49:05 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <rt.h>
#include <rt_bmp.h>

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
	//out = get_ppm(files[0]);
	out = get_anytext(files[0]);
	while (files[i] != '\0')
	{
		//out = int_join(out, get_ppm(files[i]));
		out = int_join(out, get_anytext(files[i]));
		i++;
	}
	return (out);
}
