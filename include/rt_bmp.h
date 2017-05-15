/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:42:10 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/15 12:18:13 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_BMP_H
# define RT_BMP_H
# include <libft.h>

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

#  define WORD uint16_t
#  define DWORD uint32_t
#  define LONG uint32_t
#  define O_BINARY 0

/*
* Set bit padding of the structure
*/

# pragma pack(push, 1)

/*
** file header of a standard bitmap
*/

typedef struct			s_bitmap_file_header
{
	WORD		file_type;
	DWORD		file_size;
	DWORD		reserved;
	DWORD		offset;
}						t_bitmap_file_header;

/*
** standard bitmap header
*/

typedef struct			s_dib_header
{
	DWORD		dib_size;
	LONG		width;
	LONG		height;
	WORD		planes;
	WORD		bit_count;
	DWORD		bit_compression;
	DWORD		size_image;
	LONG		x_pixels_meter;
	LONG		y_pixels_meter;
	DWORD		colors_in_tab;
	DWORD		color_important;
	DWORD		red_bmask;
	DWORD		green_bmask;
	DWORD		blue_bmask;
	DWORD		alpha_bmask;
	DWORD		color_space_type;
	char		color_space_endpoint[36];
	DWORD		gamma_red;
	DWORD		gamma_green;
	DWORD		gamma_blue;
	DWORD		intent;
	DWORD		icc_profile_data;
	DWORD		icc_profile_size;
	DWORD		reserved;
}						t_dib_header;

/*
** restores the padding/alignement from the last call of #pragma pack(push)
*/

# pragma pack(pop)

/*
** pair of bitmap header and raw data
*/

typedef struct			s_bitmap
{
	t_dib_header		info;
	unsigned char		*bmp;
}						t_bitmap;

/*
** ubmp stands for uncompressed bitmap, size should contain the size in pixels
** and data all the pixels ARGB code stored in a X + size.y * Y patern
** (left to right and top to bottom)
*/

typedef	struct			s_ubmp
{
	t_point				size;
	int					*data;
}						t_ubmp;

typedef enum	e_filetype
{
	ft_perlin,
	ft_langton,
	ft_ppm,
	ft_bmp
}				t_filetype;

t_ubmp					*ft_bmp_to_ubmp(t_bitmap *bitmap);
t_bitmap				*ft_bitmap_file_load(char *path);

int						*get_bmp(char *file);

int						get_filetype(char *filename);
int						*get_anytext(char *filename);

void					init_ppm(int fd, int **ppm, int *size, char *file);
int						*get_ppm(char *file);

void					*memjoin(unsigned char *dst, unsigned char *src,
	int sdst, int ssrc);

#endif
