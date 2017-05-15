/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:07:00 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/15 12:17:27 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_bmp.h>
#include <rt.h>

int	*get_bmp(char *file)
{
	t_bitmap		*file_bmp;
	t_ubmp			*file_unc;
	int				*img;
	int				*size;

	print_info("GET FILE START");
	file_bmp = ft_bitmap_file_load(file);
	print_info("GET FILE DONE");
	file_unc = ft_bmp_to_ubmp(file_bmp);
	print_info("SET MLX FILE DONE");
	size = (int *)ft_memalloc(sizeof(int) * 3);
	size[0] = file_unc->size.x * file_unc->size.y;
	size[1] = file_unc->size.x;
	size[2] = file_unc->size.y;
	img = (int *)memjoin((unsigned char *)size, (unsigned char *)file_unc->data,
		3 * sizeof(int), size[0]);
	return (img);
}
