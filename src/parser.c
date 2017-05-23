/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:22:27 by pgourran          #+#    #+#             */
/*   Updated: 2017/05/23 23:22:29 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define AN0 static t_scene s_alloc_scene_norme(void ***tab, t_mlx mlx);
#define AN1 static t_scene rt_alloc_scene(void ***tab, t_mlx mlx);

AN0;
AN1;

t_mlx					rt_get_parser(char *path, t_mlx mlx)
{
	char		*file;
	t_parser	*parser;
	void		***tab;

	file = rt_get_file(path);
	parser = rt_parser_file(file);
	tab = rt_list_to_tab(parser->next, mlx.tab_size);
	mlx.s = rt_alloc_scene(tab, mlx);
	if (*(((char ***)tab)[4]) != NULL)
		mlx.tex = get_texture((char **)tab[4]);
	else
	{
		mlx.tex = rt_memalloc(sizeof(int *));
		mlx.tex[0] = 0;
	}
	rt_check_value(tab, mlx.tab_size);
	rt_free_after_parser(file, parser);
	free(tab[CAMERA]);
	free(tab[TEXTURES]);
	free(tab);
	return (mlx);
}

static t_scene			rt_alloc_scene(void ***tab, t_mlx mlx)
{
	t_scene scene;

	scene = s_alloc_scene_norme(tab, mlx);
	scene.light = (t_obj *)tab[1];
	scene.cam = *((t_cam *)tab[2]);
	scene.set = (t_set *)tab[3];
	if (scene.cam.dsr < 1 || scene.cam.dsr > 4)
		scene.cam.dsr = 1;
	if (scene.cam.size.x < 100 || scene.cam.size.x > 2560)
		scene.cam.size.x = 1280;
	if (scene.cam.size.y < 100 || scene.cam.size.y > 1440)
		scene.cam.size.y = 720;
	scene.cam.size.x = scene.set->width * scene.cam.dsr;
	scene.cam.size.y = scene.set->height * scene.cam.dsr;
	scene.cam.viewplane.x = 10.0 * ((float)scene.cam.size.x
		/ (float)scene.cam.size.y);
	scene.cam.p.x = -5.0 * ((float)scene.cam.size.x / (float)scene.cam.size.y);
	scene.cam.max_reflect = scene.set->max_reflect;
	scene.cam.fast = 1;
	if (scene.cam.viewplane.z < 1 || scene.cam.size.x < scene.cam.viewplane.z)
		scene.cam.viewplane.z = 1.0;
	if (scene.cam.viewplane.w < 1 || scene.cam.size.y < scene.cam.viewplane.w)
		scene.cam.viewplane.w = 1.0;
	return (scene);
}

static t_scene			s_alloc_scene_norme(void ***tab, t_mlx mlx)
{
	t_scene scene;

	scene.n_o = mlx.tab_size[0];
	scene.n_l = mlx.tab_size[1];
	scene.obj = (t_obj *)tab[0];
	return (scene);
}
