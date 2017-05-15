/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:16:13 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/15 16:36:38 by vthomas          ###   ########.fr       */
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
	ft_putstr(filename);
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
	int	*text;

	t = get_filetype(filename);
	if (t == ft_perlin)
		text = perlin();
	else if (t == ft_langton)
		text = langton();
	else if (t == ft_ppm)
		text = get_ppm(filename);
	else if (t == ft_bmp)
		text = get_bmp(filename);
	else
		return (NULL);
	ft_putendl("    \033[32m⦗ OK ⦘\033[0m");
	return (text);
}
