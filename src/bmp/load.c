/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:07:00 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/13 19:32:37 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_bmp.h>
#include <rt.h>

int	*get_bmp(char *file)
{
	t_bitmap		*file_bmp;
	t_ubmp			*file_unc;
	t_point			p;

	print_info("GET FILE START");
	file_bmp = ft_bitmap_file_load(file);
	print_info("GET FILE DONE");
	p = (t_point){.x = (int)file_bmp->info.width,
		.y = (int)file_bmp->info.height};
	file_unc = ft_bmp_to_ubmp(file_bmp);
	return (file_unc->data);
}
