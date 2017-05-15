/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:07:00 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:20:56 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_bmp.h>
#include <rt.h>

static void print_mem(int	*mem, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		printf("%08X ", mem[i]);
		i++;
		if (i % 4 == 0)
			printf(" ");
		if (i % 8 == 0)
			printf("\n");
	}
	printf("\n");
}

int	*get_bmp(char *file)
{
	t_bitmap		*file_bmp;
	t_ubmp			*file_unc;
	int				*img;
	int				*size;

	file_bmp = ft_bitmap_file_load(file);
	file_unc = ft_bmp_to_ubmp(file_bmp);
	size = (int *)ft_memalloc(sizeof(int) * 3);
	size[0] = file_unc->size.x * file_unc->size.y + 3;
	size[1] = file_unc->size.x;
	size[2] = file_unc->size.y;
	print_info(ft_itoa(size[0]));
	print_info(ft_itoa(size[1]));
	print_info(ft_itoa(size[2]));
	img = (int *)memjoin((unsigned char *)size, (unsigned char *)file_unc->data,
		3 * sizeof(int), (size[0] - 3) * sizeof(int));
	return (img);
}
