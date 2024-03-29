/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/04/27 05:02:05 by aviau            ###   ########.fr       */
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

	ret.cam.ori.x = 0.0;
	ret.cam.ori.y = 10.0;
	ret.cam.ori.z = -18.0;

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

	ret.cam.viewplane.x = 10.0;
	ret.cam.viewplane.y = 10.0 * (700.0 / 900.0);

	ret.cam.p.x = -5.0;
	ret.cam.p.y = 5.0 * (700.0 / 900.0);
	ret.cam.p.z = 5.0;

	ret.light = ft_memalloc(sizeof(t_obj) * 5);
	ret.light[0].pos.x = 0.0;
	ret.light[0].pos.y = 10.0;
	ret.light[0].pos.z = -25.0;

	ret.light[0].col = 0xFFFFAA;
	ret.light[0].type = light;
	ret.light[0].r = 250.0;
/*	
	ret.light[1].pos.x = -1.5;
	ret.light[1].pos.y = 10.0;
	ret.light[1].pos.z = 7.0;

	ret.light[1].col = 0xFFFFFF;
	ret.light[1].type = light;
	ret.light[1].r = 100.0;
*
	ret.light[2].pos.x = 0.0;
	ret.light[2].pos.y = 25.0;
	ret.light[2].pos.z = 0.0;

	ret.light[2].col = 0x00FF00;
	ret.light[2].type = light;
	ret.light[2].r = 0.0;

	ret.light[3].pos.x = 0.0;
	ret.light[3].pos.y = 20.0;
	ret.light[3].pos.z = 20.0;

	ret.light[3].col = 0xFF0000;
	ret.light[3].type = light;
	ret.light[3].r = 0.0;
*/		
	ret.light[4].type = end;

	ret.obj = ft_memalloc(sizeof(t_obj) * 18);

	ret.obj[0].dir.x = 1.0;
	ret.obj[0].dir.y = 0.0;
	ret.obj[0].dir.z = 0.0;
	ret.obj[0].pos.x = 0.0;
	ret.obj[0].pos.y = 25.0;
	ret.obj[0].pos.z = 10.0;
	ret.obj[0].pos.w = 0.0;

	ret.obj[0].col = 0xFF902C;
	ret.obj[0].type = cylindre;
	ret.obj[0].r = 5;

	ret.obj[1].dir.x = 0.0;
	ret.obj[1].dir.y = 1.0;
	ret.obj[1].dir.z = 0.0;
	ret.obj[1].pos.x = 0.0;
	ret.obj[1].pos.y = 15.0;
	ret.obj[1].pos.z = 10.0;
	ret.obj[1].pos.w = -1.0;

	ret.obj[1].tex = 0;
	ret.obj[1].col = 0xC62731;
	ret.obj[1].type = cone;
	ret.obj[1].alpha = 30.0;

	ret.obj[2].dir.x = 1.0;
	ret.obj[2].dir.y = 1.0;
	ret.obj[2].dir.z = 0.0;
	ret.obj[2].pos.x = 0.0;
	ret.obj[2].pos.y = 15.0;
	ret.obj[2].pos.z = 10.0;
	ret.obj[2].pos.w = 0.0;

	ret.obj[2].col = 0x9D1724;
	ret.obj[2].tex = 0;
	ret.obj[2].type = cone;
	ret.obj[2].alpha = 30.0;

	ret.obj[3].dir.x = 1.0;
	ret.obj[3].dir.y = 0.0;
	ret.obj[3].dir.z = 0.0;
	ret.obj[3].pos.x = 0.0;
	ret.obj[3].pos.y = 15.0;
	ret.obj[3].pos.z = 10.0;
	ret.obj[3].pos.w = 0.0;

	ret.obj[3].tex = 0;
	ret.obj[3].col = 0x2C934B;
	ret.obj[3].type = cone;
	ret.obj[3].alpha = 30.0;

	ret.obj[4].pos.x = 12.0;
	ret.obj[4].pos.y = 0.0;
	ret.obj[4].pos.z = 0.0;
	ret.obj[4].pos.w = 0.0;

	ret.obj[4].col = 0x21763A;
	ret.obj[4].tex = 0;
	ret.obj[4].type = sphere;
	ret.obj[4].r = 3;

	ret.obj[5].pos.x = 0.0;
	ret.obj[5].pos.y = 5.0;
	ret.obj[5].pos.z = 0.0;
	ret.obj[5].pos.w = 0.0;

	ret.obj[5].col = 0x0450D5;
	ret.obj[5].tex = 0;
	ret.obj[5].type = sphere;
	ret.obj[5].r = 0.4;

	ret.obj[6].pos.x = -9.0;
	ret.obj[6].pos.y = 0.0;
	ret.obj[6].pos.z = 5.0;
	ret.obj[6].pos.w = 0.0;

	ret.obj[6].col = 0x8D3AA0;
	ret.obj[6].tex = 0;
	ret.obj[6].type = sphere;
	ret.obj[6].r = 3;

	ret.obj[7].pos.x = 3.0;
	ret.obj[7].pos.y = 0.0;
	ret.obj[7].pos.z = 5.0;
	ret.obj[7].pos.w = 0.0;

	ret.obj[7].col = 0xE8AA02;
	ret.obj[7].tex = 0;
	ret.obj[7].type = sphere;
	ret.obj[7].r = 3;

	ret.obj[8].pos.x = 9.0;
	ret.obj[8].pos.y = 0.0;
	ret.obj[8].pos.z = 5.0;
	ret.obj[8].pos.w = 0.0;

	ret.obj[8].col = 0;
	ret.obj[8].tex = 0;
	ret.obj[8].type = sphere;
	ret.obj[8].r = 3;

	ret.obj[9].pos.x = -6.0;
	ret.obj[9].pos.y = 0.0;
	ret.obj[9].pos.z = 10.0;
	ret.obj[9].pos.w = 0.0;

	ret.obj[9].col = 0x165BD9;
	ret.obj[9].tex = 0;
	ret.obj[9].type = sphere;
	ret.obj[9].r = 3;
	/////////////////////////
	ret.obj[10].pos.x = 0.0;
	ret.obj[10].pos.y = 10.0;
	ret.obj[10].pos.z = -5.0;
	ret.obj[10].pos.w = 0.0;

	ret.obj[10].col = 0xFF00FF;
	ret.obj[10].tex = 5;
	ret.obj[10].type = sphere;
	ret.obj[10].r = 3.0;
	//////////////////
	ret.obj[11].pos.x = -3.0;
	ret.obj[11].pos.y = 8.0;
	ret.obj[11].pos.z = -5.0;
	ret.obj[11].pos.w = 0.0;

	ret.obj[11].col = 0xFCE704;
	ret.obj[11].tex = 0;
	ret.obj[11].type = sphere;
	ret.obj[11].r = 2;

	ret.obj[12].pos.x = 3.0;
	ret.obj[12].pos.y = 0.0;
	ret.obj[12].pos.z = 15.0;
	ret.obj[12].pos.w = 0.0;

	ret.obj[12].col = 0x702E6F;
	ret.obj[12].tex = 0;
	ret.obj[12].type = sphere;
	ret.obj[12].r = 3;

	ret.obj[13].pos.x = 0.0;
	ret.obj[13].pos.y = 0.0;
	ret.obj[13].pos.z = 20.0;
	ret.obj[13].pos.w = 0.0;

	ret.obj[13].col = 0xFC7C1B;
	ret.obj[13].type = sphere;
	ret.obj[13].r = 3;

	ret.obj[14].dir.x = 0.0;
	ret.obj[14].dir.y = 1.0;
	ret.obj[14].dir.z = 0.0;
	ret.obj[14].pos.x = 0.0;
	ret.obj[14].pos.y = -3.0;
	ret.obj[14].pos.z = 0.0;
	ret.obj[14].pos.w = 0.0;

	ret.obj[14].col = 0xCCCCCC;
	ret.obj[14].type = plan;

	ret.obj[15].dir.x = 0.0;
	ret.obj[15].dir.y = 0.0;
	ret.obj[15].dir.z = -1.0;
	ret.obj[15].pos.x = 0.0;
	ret.obj[15].pos.y = 0.0;
	ret.obj[15].pos.z = 50.0;
	ret.obj[15].pos.w = 0.0;

	ret.obj[15].col = 0xCCCCCC;
	ret.obj[15].type = plan;
	///////////////////////////////
	ret.obj[16].dir.x = 0.0;
	ret.obj[16].dir.y = 0.0;
	ret.obj[16].dir.z = 1.0;
	ret.obj[16].pos.x = 0.0;
	ret.obj[16].pos.y = 10.0;
	ret.obj[16].pos.z = -6.5;
	ret.obj[16].pos.w = 1.0;

	ret.obj[16].col = 0xFFFFFF;
	ret.obj[16].tex = 0;
//	ret.obj[16].n_m = 0.0;
	ret.obj[16].type = cylindre;
	ret.obj[16].r = 1.5f;
	//////////////////////////////

	ret.obj[17].type = end;
	return (ret);
}

int		my_key_func(int key, void *param)
{
	if (ESC)
	{
		mlx_destroy_image(((t_mlx*)(param))->mlx, ((t_mlx*)(param))->img);
		ocl_finish(((t_mlx*)(param))->prog);
		exit(0);
	}
	else
		k_press(key, &(((t_mlx*)(param))->key));
	if (((t_mlx*)(param))->key ^ REDRAW)
		((t_mlx*)(param))->key += REDRAW;
	return (0);
}

void	dsr(t_mlx *mlx)
{
	unsigned int				r;
	unsigned int				g;
	unsigned int				b;
	int 			y;
	int 			x;
	int				xmax;
	int				ymax;

	y = 0;
	xmax = mlx->s.cam.size.x;
	ymax = mlx->s.cam.size.y;
	while (y < ymax)
	{
		x = 0;
		while (x < xmax)
		{
			r  = mlx->p[((y + 0) * xmax + (x + 0)) * 4 + 0];
			r += mlx->p[((y + 0) * xmax + (x + 1)) * 4 + 0];
			r += mlx->p[((y + 0) * xmax + (x + 2)) * 4 + 0];
			r += mlx->p[((y + 1) * xmax + (x + 0)) * 4 + 0];
			r += mlx->p[((y + 1) * xmax + (x + 1)) * 4 + 0];
			r += mlx->p[((y + 1) * xmax + (x + 2)) * 4 + 0];
			r += mlx->p[((y + 2) * xmax + (x + 0)) * 4 + 0];
			r += mlx->p[((y + 2) * xmax + (x + 1)) * 4 + 0];
			r += mlx->p[((y + 2) * xmax + (x + 2)) * 4 + 0];
			g  = mlx->p[((y + 0) * xmax + (x + 0)) * 4 + 1];
			g += mlx->p[((y + 0) * xmax + (x + 1)) * 4 + 1];
			g += mlx->p[((y + 0) * xmax + (x + 2)) * 4 + 1];
			g += mlx->p[((y + 1) * xmax + (x + 0)) * 4 + 1];
			g += mlx->p[((y + 1) * xmax + (x + 1)) * 4 + 1];
			g += mlx->p[((y + 1) * xmax + (x + 2)) * 4 + 1];
			g += mlx->p[((y + 2) * xmax + (x + 0)) * 4 + 1];
			g += mlx->p[((y + 2) * xmax + (x + 1)) * 4 + 1];
			g += mlx->p[((y + 2) * xmax + (x + 2)) * 4 + 1];
			b  = mlx->p[((y + 0) * xmax + (x + 0)) * 4 + 2];
			b += mlx->p[((y + 0) * xmax + (x + 1)) * 4 + 2];
			b += mlx->p[((y + 0) * xmax + (x + 2)) * 4 + 2];
			b += mlx->p[((y + 1) * xmax + (x + 0)) * 4 + 2];
			b += mlx->p[((y + 1) * xmax + (x + 1)) * 4 + 2];
			b += mlx->p[((y + 1) * xmax + (x + 2)) * 4 + 2];
			b += mlx->p[((y + 2) * xmax + (x + 0)) * 4 + 2];
			b += mlx->p[((y + 2) * xmax + (x + 1)) * 4 + 2];
			b += mlx->p[((y + 2) * xmax + (x + 2)) * 4 + 2];
			mlx->p[(y / 3 * xmax + x / 3) * 4 + 0] = r / 9;
			mlx->p[(y / 3 * xmax + x / 3) * 4 + 1] = g / 9;
			mlx->p[(y / 3 * xmax + x / 3) * 4 + 2] = b / 9;
			mlx->p[(y / 3 * xmax + x / 3) * 4 + 3] = 0;
			x += 3;
		}
		y += 3;
	}
}

int		ray_loop(t_mlx *mlx)
{
	if (mlx->key & REDRAW)
	{
		k_apply(mlx->key, &mlx->s);
		mlx->s.cam.ori.x += (mlx->key & POS_XP) ? 1 : 0;
		mlx->s.cam.ori.x -= (mlx->key & POS_XM) ? 1 : 0;
		ocl_enqueue_kernel(&(mlx->prog), "raytracer");
		dsr(mlx);
/*		int x;
		int y = -1;
		while (++y < mlx->tex[2])
		{
			x = -1;
			while (++x < mlx->tex[1])
			{
				mlx->p[(y * mlx->s.cam.size.x + x) * 4 + 2] = (mlx->tex[y * mlx->tex[1] + x + 3] & 0xFF0000) / 0x10000;
				mlx->p[(y * mlx->s.cam.size.x + x) * 4 + 1] = (mlx->tex[y * mlx->tex[1] + x + 3] & 0x00FF00) / 0x100;
				mlx->p[(y * mlx->s.cam.size.x + x) * 4 + 0] = (mlx->tex[y * mlx->tex[1] + x + 3] & 0x0000FF);
				mlx->p[(y * mlx->s.cam.size.x + x) * 4 + 3] = 0;
			}
		}
*/		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		mlx->key -= REDRAW;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	size_t	pws[2];

	if (ac < 1 || !(av))
		return (0);
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);
	mlx.s = ft_init_scene();
	mlx.tex = get_texture(&av[1]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "rtvocl");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.p = (unsigned char *)mlx_get_data_addr(mlx.img, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.p[0] = 0;
	mlx.key = REDRAW;
	pws[0] = WIDTH;
	pws[1] = HEIGHT;
	ocl_new_kernel(&(mlx.prog), 5, pws, "norowowowowd", "raytracer", WIDTH * HEIGHT
			* sizeof(int), mlx.p, sizeof(t_cam), &(mlx.s.cam), sizeof(t_obj) * 18, 
			mlx.s.obj, sizeof(t_obj) * 5, mlx.s.light, sizeof(int) * (mlx.tex[0] + 1), mlx.tex, 2);
	mlx_hook(mlx.win, 2, (1L << 0), my_key_func, &mlx);
	mlx_hook(mlx.win, 3, (1L << 1), &k_rel, &mlx);
	mlx_loop_hook(mlx.mlx, ray_loop, &mlx);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
