/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/19 01:23:18 by pgourran         ###   ########.fr       */
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

t_scene	ft_init_scene(void)
{
	t_scene	ret;

	ret.cam.ori.x = 0;
	ret.cam.ori.y = 3;
	ret.cam.ori.z = 0;

	ret.cam.dirx.x = 1.0;
	ret.cam.dirx.y = 0.0;
	ret.cam.dirx.z = 0.0;
	ret.cam.dirx = vec_norm(ret.cam.dirx);

	ret.cam.diry.x = 0.0;
	ret.cam.diry.y = 1.0;
	ret.cam.diry.z = 0.0;
	ret.cam.diry = vec_norm(ret.cam.diry);

	ret.cam.dirz.x = 0.0;
	ret.cam.dirz.y = -0.0;
	ret.cam.dirz.z = 1.0;
	ret.cam.dirz = vec_norm(ret.cam.dirz);

	ret.cam.size.x = WIDTH;
	ret.cam.size.y = HEIGHT;

	ret.cam.viewplane.x = 10;
	ret.cam.viewplane.y = 10.0 * (700.0 / 900.0);

	ret.cam.p.x = -5;
	ret.cam.p.y = 5.0 * (700.0 / 900.0);
	ret.cam.p.z = 5;

	ret.light = ft_memalloc(sizeof(t_obj) * 2);
	ret.light[0].pos.x = 0;
	ret.light[0].pos.y = 0;
	ret.light[0].pos.z = 2;

	ret.light[0].col = 0xFFFFFF;
	ret.light[0].type = light;
	ret.light[0].r = 50;
	ret.light[1].type = end;

	ret.obj = ft_memalloc(sizeof(t_obj) * 7);

	ret.obj[0].pos.x = 0;
	ret.obj[0].pos.y = 0;
	ret.obj[0].pos.z = 10;

	ret.obj[0].col = 0xFFFFFF;
	ret.obj[0].type = sphere;
	ret.obj[0].r = 2;
	ret.obj[0].diff = 0.8f;
	ret.obj[0].refl = 0.2f;
	ret.obj[0].refr = 0;

	ret.obj[1].pos.x = 2;
	ret.obj[1].pos.y = 0;
	ret.obj[1].pos.z = 10;

	ret.obj[1].col = 0xFF0000;
	ret.obj[1].type = sphere;
	ret.obj[1].r = 1;

	ret.obj[2].pos.x = 0;
	ret.obj[2].pos.y = 0;
	ret.obj[2].pos.z = 0;

	ret.obj[2].dir.x = 0;
	ret.obj[2].dir.y = -1;
	ret.obj[2].dir.z = 0;

	ret.obj[2].col = 0xFF00;
	ret.obj[2].type = plan;

	ret.obj[3].p1.x = 0;
	ret.obj[3].p1.y = 2;
	ret.obj[3].p1.z = 5;

	ret.obj[3].p2.x = 0;
	ret.obj[3].p2.y = 1;
	ret.obj[3].p2.z = 5;

	ret.obj[3].p3.x = 3;
	ret.obj[3].p3.y = 1;
	ret.obj[3].p3.z = 5;

	ret.obj[3].col = 0xFFF;
	ret.obj[3].type = triangle;


	ret.obj[4].pos.x = 2;
	ret.obj[4].pos.y = 3;
	ret.obj[4].pos.z = 10;

	ret.obj[4].r = 2;
	ret.obj[4].col = 0xFF00FF;
	ret.obj[4].type = sphere;

	ret.obj[5].pos.x = 2;
	ret.obj[5].pos.y = 3;
	ret.obj[5].pos.z = 10;

	ret.obj[5].alpha = M_PI / 16;
	ret.obj[5].col = 0xFFFFFF;
	ret.obj[5].type = cone;

	ret.obj[6].type = end;
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

	if (ac != 1 || !(av))
		return (0);
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);
	mlx.s = ft_init_scene();
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "rtvocl");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.p = mlx_get_data_addr(mlx.img, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.p[0] = 0;
	pws[0] = WIDTH;
	pws[1] = HEIGHT;
	ocl_new_kernel(&(mlx.prog), 4, pws, "norowowowd", "raytracer", WIDTH * HEIGHT
		* sizeof(int), mlx.p, sizeof(t_cam), &(mlx.s.cam), sizeof(t_obj) * 7, 
		mlx.s.obj, sizeof(t_obj), mlx.s.light, 2);
	ocl_enqueue_kernel(&(mlx.prog), "raytracer");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 2, (1L << 0), my_key_func, &mlx);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
