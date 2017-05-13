/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:42:10 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/13 19:16:06 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_BMP_H
# define RT_BMP_H
# include <libft.h>

/*
* Set bit padding of the structure
*/

# pragma pack(push, 1)

/*
** file header of a standard bitmap
*/
typedef struct			s_bitmap_file_header
{
	unsigned short		file_type;
	unsigned long		file_size;
	unsigned long		reserved;
	unsigned long		offset;
}						t_bitmap_file_header;

/*
** standard bitmap header
*/
typedef struct			s_dib_header
{
	unsigned long		dib_size;
	long				width;
	long				height;
	unsigned short		planes;
	unsigned short		bit_count;
	unsigned long		bit_compression;
	unsigned long		size_image;
	long				x_pixels_meter;
	long				y_pixels_meter;
	unsigned long		colors_in_tab;
	unsigned long		color_important;
	unsigned long		red_bmask;
	unsigned long		green_bmask;
	unsigned long		blue_bmask;
	unsigned long		alpha_bmask;
	unsigned long		color_space_type;
	char				color_space_endpoint[36];
	unsigned long		gamma_red;
	unsigned long		gamma_green;
	unsigned long		gamma_blue;
	unsigned long		intent;
	unsigned long		icc_profile_data;
	unsigned long		icc_profile_size;
	unsigned long		reserved;
}						t_dib_header;

/*
* restore bit padding of the padding
*/
# pragma pack(pop)

/*
** pair of bitmap header and raw data
*/
typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

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

#endif
