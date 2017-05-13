/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 18:31:23 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/13 20:43:17 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_bmp.h>

static void				*sf_bmp_file_load_error(int fd, t_bitmap *out)
{
	if (out)
	{
		print_log("Error 1");
		if (out->bmp)
			ft_memdel((void **)&(out->bmp));
		print_log("Error 2");
		ft_memdel((void **)&out);
		print_log("part 3");
	}
	close(fd);
	return (NULL);
}

inline static t_bitmap	*sf_bitmap_file_load(t_bitmap *out, int i, int fd,
										t_bitmap_file_header header)
{
	if ((out->bmp = (unsigned char *)ft_memalloc(sizeof(unsigned char *) *
			out->info.size_image) + 3) == NULL)
		return (sf_bmp_file_load_error(fd, out));
	print_log("part 1");
	i = header.offset - out->info.dib_size - sizeof(t_bitmap_file_header);
	print_log("part 2");
	if (lseek(fd, i, SEEK_CUR) < i)
		return (sf_bmp_file_load_error(fd, out));
	print_log("part 3");
	if (read(fd, out->bmp, out->info.size_image) <
		(int)out->info.size_image)
		return (sf_bmp_file_load_error(fd, out));
	print_log("part 4");
	close(fd);
	print_log("part 5");
	return (out);
}

t_bitmap				*ft_bitmap_file_load(char *path)
{
	t_bitmap_file_header	header;
	t_bitmap				*out;
	int						fd;
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
	print_log("SET OK");
	if (read(fd, &(out->info.dib_size), i) < i)
	{
		print_info("NO READ");
		return (sf_bmp_file_load_error(fd, out));
	}
	if (!(i = out->info.dib_size - sizeof(unsigned long)))
	{
		print_info("SIZE ERROR LOL");
		return (sf_bmp_file_load_error(fd, out));
	}
	if (read(fd, &(out->info.width), i) < i)
	{
		print_info("NO SECOND READ LOL");
		return (sf_bmp_file_load_error(fd, out));
	}
	print_log("GOING TO SF FUNCTION");;
	return (sf_bitmap_file_load(out, i, fd, header));
}
