#include "parser.h"

static t_scene	*rt_alloc_scene(void *** tab);

t_scene			rt_get_parser(char *path)
{
	char		*file;
	t_parser	*parser;
	t_scene		*scene;
	void		***tab;

	file = rt_get_file(path);
	parser = rt_parser_file(file);
	tab = rt_list_to_tab(parser);
	scene = rt_alloc_scene(tab);
	rt_free_after_parser(file, parser);
	return (*scene);
}

static t_scene			*rt_alloc_scene(void *** tab)
{
	t_scene *scene;

	scene = (t_scene *)rt_memalloc(sizeof(t_scene));
	scene->obj = (t_obj *)tab[0];
	scene->light = (t_obj *)tab[1];
	scene->cam = *((t_cam *)tab[2]);
	scene->set = (t_set *)tab[3];
	return (scene);
}
