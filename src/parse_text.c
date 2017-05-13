/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:16:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/13 19:48:26 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt.h>
#include <rt_bmp.h>

int	get_filetype(char *filename)
{
	int		i;
	char	*ext;

	i = ft_strlen(filename);
	if (i < 5)
		return (-1);
	ext = ft_strrchr(filename, '.');
	if (ext == NULL)
	{
		if (ft_strcmp(filename, "perlin") == 0)
			return (ft_perlin);
		else if (ft_strcmp(filename, "langton") == 0)
			return (ft_langton);
		else
			return (-1);
	}
	if (ft_strcmp(ext, ".ppm") == 0)
		return (ft_ppm);
	else if (ft_strcmp(ext, ".bmp") == 0)
		return (ft_bmp);
	return (-1);
}

int	*get_anytext(char *filename)
{
	int	t;

	t = get_filetype(filename);
	if (t == ft_perlin)
		return (perlin());
	else if (t == ft_langton)
		return (langton());
	else if (t == ft_ppm)
		return (get_ppm(filename));
	else if (t == ft_bmp)
		return (get_bmp(filename));
	else
		return (NULL);
}
