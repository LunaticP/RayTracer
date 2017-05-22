#include "parser.h"

static t_scene	rt_alloc_scene(void ***tab, t_mlx mlx);

// static void			s_print_all(void ***tab, int *tab_size);
// static void			s_print_objects(t_obj *obj);
// static void			s_print_lights(t_obj *obj);
// static void			s_print_camera(t_cam *cam);
// static void			s_print_textures(char **tab);
// static void			s_print_tab_size(int *tab);
// static void			s_print_settings(t_set *set);

t_mlx			rt_get_parser(char *path, t_mlx mlx)
{
	char		*file;
	t_parser	*parser;
	void		***tab;

	file = rt_get_file(path);
	parser = rt_parser_file(file);
	tab = rt_list_to_tab(parser->next, mlx.tab_size); // gerer le tab[4] -> textures
	mlx.s = rt_alloc_scene(tab, mlx);
	if (*(((char ***)tab)[4]) != NULL)
		mlx.tex = get_texture((char **)tab[4]);
	else
	{
		mlx.tex = rt_memalloc(sizeof(int *));
		mlx.tex[0] = 0;
	}
	rt_check_value(tab);
	rt_free_after_parser(file, parser); // free les str
	// if (DEBUG)
	// {
	// 	s_print_all(tab, mlx.tab_size);
	// 	exit(0);
	// }
	return (mlx);
}

static t_scene			rt_alloc_scene(void ***tab, t_mlx mlx)
{
	t_scene scene;

	scene.n_o = mlx.tab_size[0];
	scene.n_l = mlx.tab_size[1];
	scene.obj = (t_obj *)tab[0];
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
	scene.cam.viewplane.x = 10.0 * ((float)scene.cam.size.x / (float)scene.cam.size.y);
	scene.cam.p.x = -5.0 * ((float)scene.cam.size.x / (float)scene.cam.size.y);
	return (scene);
}

// void			print_data_camera(t_cam *cam)
// {
// 	printf("ori.x : %f | ori.y : %f | ori.z : %f\n", cam->ori.x, cam->ori.y, cam->ori.z);
// 	printf("dirx.x : %f | dirx.y : %f | dirx.z : %f\n", cam->dirx.x, cam->dirx.y, cam->dirx.z);
// 	printf("diry.x : %f | diry.y : %f | diry.z : %f\n", cam->diry.x, cam->diry.y, cam->diry.z);
// 	printf("dirz.x : %f | dirz.y : %f | dirz.z : %f\n", cam->dirz.z, cam->dirz.y, cam->dirz.z);
// 	// printf("size.x : %d | size.y : %d\n", cam->size.x, cam->size.y);
// 	printf("viewplane.x : %f | viewplane.y : %f | viewplane.z : %f | viewplane.w : %f\n", cam->viewplane.x, cam->viewplane.y, cam->viewplane.z, cam->viewplane.w);
// 	printf("p.x : %f | p.y : %f | p.z : %f\n", cam->p.x, cam->p.y, cam->p.z);
// 	printf("chunk.x : %f | chunk.y : %f\n", cam->chunk.x, cam->chunk.y);
// 	printf("fast : %d | dsr : %d\n", cam->fast, cam->dsr);
// 	printf("________\n");
// }

// void			print_data_settings(t_set *set)
// {
// 	printf("width : %d | height : %d\n", set->width, set->height);
// 	printf("max_reflect : %d | anti_allias : %d | ambient : %d | stereo : %f\n", set->max_reflect, set->anti_allias, set->ambient, set->stereo);
// 	printf("name : %s\n", set->name);	
// }

// void			print_data_obj(t_obj *obj)
// {
// 	printf("pos.x : %f | pos.y : %f | pos.z : %f | pos.w : %f\n", obj->pos.x, obj->pos.y, obj->pos.z, obj->pos.w);
// 	printf("dir.x : %f | dir.y : %f | dir.z : %f | dir.w : %f\n", obj->dir.x, obj->dir.y, obj->dir.z, obj->dir.w);
// 	printf("tet : %f\n", obj->tet);
// 	printf("phi : %f\n", obj->phi);
// 	printf("rot : %f\n", obj->rot);
// 	printf("min.x : %f | min.y : %f | min.z : %f | min.w : %f\n", obj->min.x, obj->min.y, obj->min.z, obj->min.w);
// 	printf("max.x : %f | max.y : %f | max.z : %f | max.w : %f\n", obj->max.x, obj->max.y, obj->max.z, obj->max.w);
// 	printf("col : %d\n", obj->col);
// 	printf("diff : %f | refl : %f | trans : %f | refr : %f\n", obj->diff, obj->refl, obj->trans, obj->refr);
// 	printf("r : %f\n", obj->r);
// 	printf("su : %f | sd : %f\n", obj->su, obj->sd);
// 	printf("alpha : %f\n", obj->alpha);	
// 	printf("caps : %d\n", obj->caps);
// 	printf("p1.x : %f | p1.y : %f | p1.z : %f\n", obj->p1.x, obj->p1.y, obj->p1.z);
// 	printf("p2.x : %f | p2.y : %f | p2.z : %f\n", obj->p2.x, obj->p2.y, obj->p2.z);
// 	printf("p3.x : %f | p3.y : %f | p3.z : %f\n", obj->p3.x, obj->p3.y, obj->p3.z);
// 	printf("tex : %hd | n_m : %hd | r_m : %hd | t_m : %hd\n", obj->tex, obj->n_m, obj->r_m, obj->t_m);
// 	printf("type : %d\n", obj->type);
// 	printf("mod_tex.x : %f, mod_tex.y : %f, mod_tex.z : %f, mod_tex.w : %f\n", obj->mod_tex.x, obj->mod_tex.y, obj->mod_tex.z, obj->mod_tex.w);
// 	printf("mod_normal.x : %f, mod_normal.y : %f, mod_normal.z : %f, mod_normal.w : %f\n", obj->mod_normal.x, obj->mod_normal.y, obj->mod_normal.z, obj->mod_normal.w);
// 	printf("mod_ref.x : %f, mod_ref.y : %f, mod_ref.z : %f, mod_ref.w : %f\n", obj->mod_ref.x, obj->mod_ref.y, obj->mod_ref.z, obj->mod_ref.w);
// 	printf("mod_trans.x : %f, mod_trans.y : %f, mod_trans.z : %f, mod_trans.w : %f\n", obj->mod_trans.x, obj->mod_trans.y, obj->mod_trans.z, obj->mod_trans.w);
// 	printf("________\n");
// }

// static void			s_print_all(void ***tab, int *tab_size)
// {
// 	s_print_objects((t_obj *)tab[0]);
// 	s_print_lights((t_obj *)tab[1]);
// 	s_print_camera((t_cam *)tab[2]);
// 	s_print_settings((t_set *)tab[3]);
// 	s_print_textures((char *)tab[4]);
// 	s_print_tab_size(tab_size);
// }

// static void			s_print_objects(t_obj *obj)
// {
// 	printf("________\nOBJECTS :\n\n");
// 	while (obj->type != end)
// 		print_data_obj(obj++);
// }

// static void			s_print_lights(t_obj *obj)
// {
// 	printf("________\nLIGHTS :\n\n");
// 	while (obj->type != end)
// 		print_data_obj(obj++);
// }

// static void			s_print_camera(t_cam *cam)
// {
// 	printf("________\nCAMERA :\n\n");
// 	print_data_camera(cam);
// }

// static void			s_print_settings(t_set *set)
// {
// 	printf("________\nSETTINGS :\n\n");
// 	print_data_settings(set);
// }

// static void			s_print_textures(char **tab)
// {
// 	printf("________\nTEXTURES :\n\n");
// 	while (*tab)
// 		printf("%s\n", *tab++);
// }

// static void			s_print_tab_size(int *tab)
// {
// 	printf("________\nTAB_SIZE :\n");
// 	printf("%d\n", tab[0]);
// 	printf("%d\n", tab[1]);
// 	printf("%d\n", tab[2]);
// 	printf("%d\n", tab[3]);
// 	printf("%d\n", tab[4]);
// }
