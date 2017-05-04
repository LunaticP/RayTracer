#include "parser.h"

static t_scene	rt_alloc_scene(void ***tab);

// now return t_mlx et prend le t_mlx en param [pouvoir gerer plusieurs ordre]

t_mlx			rt_get_parser(char *path, t_mlx mlx)
{
	char		*file;
	t_parser	*parser;
	void		***tab;

	file = rt_get_file(path);
	parser = rt_parser_file(file);
	tab = rt_list_to_tab(parser); // gerer le tab[4] -> textures
	mlx.s = rt_alloc_scene(tab);
	mlx.tex = (int *)get_texture((char **)tab[4]);
	// LINK tab[4] texture a la MLX
	// rt_free_after_parser(file, parser); // free les str
	printf("%d\n");
	exit_error("SAVE EXIT : Need to check if texture is correct BEFORE");

	// print_data_obj(scene->obj);
	// print_data_obj(scene->light);
	// print_data_camera(&scene->cam);
	// exit(0);

	return (mlx);
}

static t_scene			rt_alloc_scene(void ***tab)
{
	t_scene scene;

	// scene = (t_scene *)rt_memalloc(sizeof(t_scene));
	scene.obj = (t_obj *)tab[0];
	scene.light = (t_obj *)tab[1];
	scene.cam = *((t_cam *)tab[2]);
	scene.set = (t_set *)tab[3];
	return (scene);
}

void			print_data_camera(t_cam *cam)
{
	printf("ori.x : %f | ori.y : %f | ori.z : %f\n", cam->ori.x, cam->ori.y, cam->ori.z);
	printf("dirx.x : %f | dirx.y : %f | dirx.z : %f\n", cam->dirx.x, cam->dirx.y, cam->dirx.z);
	printf("diry.x : %f | diry.y : %f | diry.z : %f\n", cam->diry.x, cam->diry.y, cam->diry.z);
	printf("dirz.x : %f | dirz.y : %f | dirz.z : %f\n", cam->dirz.z, cam->dirz.y, cam->dirz.z);
	printf("p.x : %f | p.y : %f | p.z : %f\n", cam->p.x, cam->p.y, cam->p.z);
	printf("viewplane.x : %f | viewplane.y : %f\n", cam->viewplane.x, cam->viewplane.y);
	printf("size.x : %d | size.y : %d\n", cam->size.x, cam->size.y);
	printf("____________\n");
}

void		print_data_obj(t_obj *obj)
{
	printf("pos.x : %f | pos.y : %f | pos.z : %f | pos.w : %f\n", obj->pos.x, obj->pos.y, obj->pos.z, obj->pos.w);
	printf("dir.x : %f | dir.y : %f | dir.z : %f | dir.w : %f\n", obj->dir.x, obj->dir.y, obj->dir.z, obj->dir.w);
	printf("tet : %f\n", obj->tet);
	printf("phi : %f\n", obj->phi);
	printf("rot : %f\n", obj->rot);
	printf("min.x : %f | min.y : %f | min.z : %f | min.w : %f\n", obj->min.x, obj->min.y, obj->min.z, obj->min.w);
	printf("max.x : %f | max.y : %f | max.z : %f | max.w : %f\n", obj->max.x, obj->max.y, obj->max.z, obj->max.w);
	printf("col : %d\n", obj->col);
	printf("diff : %f | refl : %f | trans : %f | refr : %f\n", obj->diff, obj->refl, obj->trans, obj->refr);
	printf("r : %f\n", obj->r);
	printf("su : %f | sd : %f\n", obj->su, obj->sd);
	printf("alpha : %f\n", obj->alpha);	
	printf("caps : %d\n", obj->caps);
	printf("p1.x : %f | p1.y : %f | p1.z : %f\n", obj->p1.x, obj->p1.y, obj->p1.z);
	printf("p2.x : %f | p2.y : %f | p2.z : %f\n", obj->p2.x, obj->p2.y, obj->p2.z);
	printf("p3.x : %f | p3.y : %f | p3.z : %f\n", obj->p3.x, obj->p3.y, obj->p3.z);
	printf("tex : %hd | n_m : %hd", obj->tex, obj->n_m);
	printf("type : %d\n", obj->type);
	printf("____________\n");
}
