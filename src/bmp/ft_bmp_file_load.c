/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 18:31:23 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/13 19:37:14 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_bmp.h>

static void				*sf_bmp_file_load_error(int fd, t_bitmap *out)
{
	if (out)
	{
		if (out->bmp)
			free(out->bmp);
		free(out);
	}
	close(fd);
	return (NULL);
}

inline static t_bitmap	*sf_bitmap_file_load(t_bitmap *out, int i, int fd,
										t_bitmap_file_header header)
{
	if ((out->bmp = (unsigned char*)ft_memalloc(sizeof(unsigned char*) *
			out->info.size_image)) == NULL)
		return (sf_bmp_file_load_error(fd, out));
	i = header.offset - out->info.dib_size - sizeof(t_bitmap_file_header);
	if (lseek(fd, i, SEEK_CUR) < i)
		return (sf_bmp_file_load_error(fd, out));
	if (read(fd, out->bmp, out->info.size_image) <
		(int)out->info.size_image)
		return (sf_bmp_file_load_error(fd, out));
	close(fd);
	return (out);
}

t_bitmap				*ft_bitmap_file_load(char *path)
{
	int						fd;
	t_bitmap_file_header	header;
	t_bitmap				*out;
	int						i;

	if (path == NULL || (fd = open(path, O_RDONLY, 0)) == -1)
		return (NULL);
	print_log("PATH OK");
	out = NULL;
	if (read(fd, &header, sizeof(t_bitmap_file_header))
		< (int)sizeof(t_bitmap_file_header) || header.file_type != 0x4D42
		|| (out = (t_bitmap*)ft_memalloc(sizeof(t_bitmap))) == NULL)
		return (sf_bmp_file_load_error(fd, out));
	print_log("HEADER READ OK");
	out->info = (t_dib_header){.dib_size = 0};
	print_log("SET BASE OK");
	i = (int)sizeof(unsigned long);
	if (read(fd, &(out->info.dib_size), i) < i
		|| !(i = out->info.dib_size - sizeof(unsigned long))
		|| read(fd, &(out->info.width), i) < i)
		return (sf_bmp_file_load_error(fd, out));
	print_log("GOING TO SF FUNCTION");
	return (sf_bitmap_file_load(out, i, fd, header));
}
