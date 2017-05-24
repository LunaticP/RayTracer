/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:28:19 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/24 20:47:30 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt_bmp.h>

static void				*sf_bmp_file_load_error(int fd, t_bitmap *out)
{
	if (out)
	{
		if (out->bmp)
			ft_memdel((void **)&(out->bmp));
		ft_memdel((void **)&out);
	}
	if(out)
		;
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

	if (path == NULL || (fd = open(path, O_RDONLY | O_BINARY, 0)) == -1)
		return (NULL);
	out = NULL;
	if (read(fd, &header, sizeof(t_bitmap_file_header))
		< (int)sizeof(t_bitmap_file_header) || header.file_type != 0x4D42
		|| (out = (t_bitmap*)ft_memalloc(sizeof(t_bitmap))) == NULL)
		return (sf_bmp_file_load_error(fd, out));
	out->info = (t_dib_header){.dib_size = 0};
	i = (int)sizeof(DWORD);
	if (read(fd, &(out->info.dib_size), i) < i
		|| !(i = out->info.dib_size - sizeof(DWORD))
		|| read(fd, &(out->info.width), i) < i)
		return (sf_bmp_file_load_error(fd, out));
	return (sf_bitmap_file_load(out, i, fd, header));
}
