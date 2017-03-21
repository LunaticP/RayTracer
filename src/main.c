/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/21 17:09:43 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

cl_float4		vec_norm(cl_float4 vec)
{
	// Tout est dans ce lien
	// http://www.fundza.com/vectors/normalize/
	cl_float4	norm;
	float	lenght;

	lenght = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	norm.x = vec.x / lenght;
	norm.y = vec.y / lenght;
	norm.z = vec.z / lenght;
	return (norm);
}

void	insert_obj(t_obj *tab, t_list *obj)
{
	int		i;
	t_triangle	*t;
	t_list		*k;

	k = obj;
	i = 0;
	while(k->next)
	{
		ft_putstr("yolo");
		tab[++i].type = triangle;
		t = k->content;
		tab[i].col = 0xFFFFFF;
		tab[i].p1.x = t->p1.x;
		printf("%f", tab[i].p1.x);
		tab[i].p1.y = t->p1.y;
		tab[i].p1.z = t->p1.z;
		tab[i].p2.x = t->p2.x;
		tab[i].p2.y = t->p2.y;
		tab[i].p2.z = t->p2.z;
		tab[i].p3.x = t->p3.x;
		tab[i].p3.y = t->p3.y;
		tab[i].p3.z = t->p3.z;
		tab[i].dir.x = (t->vn1.x + t->vn2.x + t->vn3.x) / 3;
		tab[i].dir.y = (t->vn1.y + t->vn2.y + t->vn3.y) / 3;
		tab[i].dir.z = (t->vn1.z + t->vn2.z + t->vn3.z) / 3;
		k = k->next;
	}
}

t_scene	ft_init_scene(t_list *obj)
{
	t_scene	ret;
	int		lenobj;
	ret.cam.ori.x = 0;
	ret.cam.ori.y = 0;
	ret.cam.ori.z = -20;

	ret.cam.dirx.x = 1.0;
	ret.cam.dirx.y = 0.0;
	ret.cam.dirx.z = 0.0;
	ret.cam.dirx = vec_norm(ret.cam.dirx);

	ret.cam.diry.x = 0.0;
	ret.cam.diry.y = 1.0;
	ret.cam.diry.z = 0.0;
	ret.cam.diry = vec_norm(ret.cam.diry);

	ret.cam.dirz.x = 0.0;
	ret.cam.dirz.y = 0.0;
	ret.cam.dirz.z = 1.0;
	ret.cam.dirz = vec_norm(ret.cam.dirz);

	ret.cam.size.x = WIDTH;
	ret.cam.size.y = HEIGHT;

	ret.cam.viewplane.x = 10;
	ret.cam.viewplane.y = 10.0 * ((float)HEIGHT / (float)WIDTH);

	ret.cam.p.x = -5;
	ret.cam.p.y = 5.0 * ((float)HEIGHT / (float)WIDTH);
	ret.cam.p.z = 5;

	ret.light = ft_memalloc(sizeof(t_obj) * 6);
	ret.light[0].pos.x = 10;
	ret.light[0].pos.y = 2.5;
	ret.light[0].pos.z = -1.0;

	ret.light[0].col = 0xFF;
	ret.light[0].type = light;
	ret.light[0].r = 100;

	ret.light[1].pos.x = -12.5;
	ret.light[1].pos.y = -12.5;
	ret.light[1].pos.z = -11.0;

	ret.light[1].col = 0xFF00;
	ret.light[1].type = light;
	ret.light[1].r = 100;

	ret.light[2].pos.x = 12.5;
	ret.light[2].pos.y = -12.5;
	ret.light[2].pos.z = -11.0;

	ret.light[2].col = 0xFF0000;
	ret.light[2].type = light;
	ret.light[2].r = 100;

	ret.light[3].pos.x = -20.0;
	ret.light[3].pos.y = 10.0;
	ret.light[3].pos.z = 25.0;

	ret.light[3].col = 0xFFFFFF;
	ret.light[3].type = light;
	ret.light[3].r = 100;

	ret.light[4].pos.x = 20.0;
	ret.light[4].pos.y = 10.0;
	ret.light[4].pos.z = 25.0;

	ret.light[4].col = 0xFFFFFF;
	ret.light[4].type = light;
	ret.light[4].r = 100;

	ret.light[5].type = end;
	lenobj = ft_lstlen(obj);
	ret.obj = ft_memalloc(sizeof(t_obj) * (6 + lenobj));

	ret.obj[0].pos.x = 4.0;
	ret.obj[0].pos.y = 8.0;
	ret.obj[0].pos.z = 4.0;

	ret.obj[0].col = 0xFFFFFF;
	ret.obj[0].type = sphere;
	ret.obj[0].r = 5.0;
	ret.obj[0].diff = 0.8f;
	ret.obj[0].refl = 0.2f;
	ret.obj[0].refr = 0.0;

	ret.obj[3].pos.x = -10.0;
	ret.obj[3].pos.y = -3.0;
	ret.obj[3].pos.z = 20.1;

	ret.obj[3].dir.x = 0.0;
	ret.obj[3].dir.y = 0.0;
	ret.obj[3].dir.z = -1.0;

	ret.obj[3].col = 0xFFFFFF;
	ret.obj[3].type = plan;

	ret.obj[4].pos.x = -10.0;
	ret.obj[4].pos.y = 6.0;
	ret.obj[4].pos.z = 20.0;

	ret.obj[4].dir.x = 0.0;
	ret.obj[4].dir.y = -3.0;
	ret.obj[4].dir.z = 0.0;

	ret.obj[4].col = 0xFFFFFF;
	ret.obj[4].type = plan;


	ret.obj[1].pos.x = 10.0;
	ret.obj[1].pos.y = 10.0;
	ret.obj[1].pos.z = 10.0;

	ret.obj[1].r = 1.5;
	ret.obj[1].col = 0xFFFFFF;
	ret.obj[1].type = sphere;

	ret.obj[2].pos.x = 2.0;
	ret.obj[2].pos.y = 3.0;
	ret.obj[2].pos.z = 10.0;
	ret.obj[2].r = 1.5;

	ret.obj[2].alpha = M_PI / 16.0;
	ret.obj[2].col = 0xFFFFFF;
	ret.obj[2].type = sphere;
//	insert_obj(&ret.obj[5], obj);
	ret.obj[5 + lenobj].type = end;
	return (ret);
}
/*
cl_float4	*ocl_new_image(cl_float4 *img, int width, int height)
{
	img = malloc(width * height * sizeof(cl_float4));

}
*/
int		my_key_func(int keycode, void *param)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(((t_mlx*)(param))->mlx, ((t_mlx*)(param))->img);
		ocl_finish(((t_mlx*)(param))->prog);
		exit(0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	size_t	pws[2];
	t_list	*obj;

	if (ac != 1 || !(av))
		return (0);
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);
	obj = get_obj("ico.obj");
	mlx.s = ft_init_scene(obj);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "rtvocl");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.p = mlx_get_data_addr(mlx.img, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.p[0] = 0;
	pws[0] = WIDTH;
	pws[1] = HEIGHT;
	ocl_new_kernel(&(mlx.prog), 4, pws, "norowowowd", "raytracer", WIDTH * HEIGHT
		* sizeof(int), mlx.p, sizeof(t_cam), 
		&(mlx.s.cam), sizeof(t_obj) * (6 + ft_lstlen(obj)), 
		mlx.s.obj, sizeof(t_obj) * 6, mlx.s.light, 2);
	ocl_enqueue_kernel(&(mlx.prog), "raytracer");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 2, (1L << 0), my_key_func, &mlx);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
