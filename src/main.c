/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/02 06:49:19 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

# define STEREO		0
# define OUT_FILE	0

cl_float4		vec_norm(cl_float4 vec)
{
	cl_float4	norm;
	float	lenght;

	lenght = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	norm.x = vec.x / lenght;
	norm.y = vec.y / lenght;
	norm.z = vec.z / lenght;
	return (norm);
}

void		polar_to_vec(float tet, float phi, cl_float4 *dir)
{
	dir->x = sin(tet) * cos(phi);
	dir->z = cos(phi);
	dir->y = sin(tet) * sin(phi);
}

void		vec_to_polar(float *tet, float *phi, cl_float4 dir)
{
	*tet = acos(dir.y);
	*phi = atan2(dir.z, dir.x);
}

t_scene	ft_init_scene(void)
{
	t_scene	ret;

	ret.cam.ori.x = 0.0;
	ret.cam.ori.y = -7.0;
	ret.cam.ori.z = -14.0;

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
	ret.cam.dirz.z = 0.1;
	ret.cam.dirz = vec_norm(ret.cam.dirz);

	ret.cam.size.x = WIDTH;
	ret.cam.size.y = HEIGHT;

	ret.cam.viewplane.x = 10.0 * ((float)(WIDTH) / (float)(HEIGHT));
	ret.cam.viewplane.y = 10.0;

	ret.cam.p.x = -5.0 * ((float)(WIDTH) / (float)(HEIGHT));
	ret.cam.p.y = 5.0;
	ret.cam.p.z = 5.0;

	ret.light = ft_memalloc(sizeof(t_obj) * 7);
	ret.light[0].pos.x = 0.0;
	ret.light[0].pos.y = 0.0;
	ret.light[0].pos.z = -5.0;
	ret.light[0].col = 0x00FFFF;
	ret.light[0].type = light;
	ret.light[0].r = 35.0;

	ret.light[1].pos.x = 0.0;
	ret.light[1].pos.y = 0.0;
	ret.light[1].pos.z = 5.0;
	ret.light[1].col = 0xFF00FF;
	ret.light[1].type = light;
	ret.light[1].r = 35.0;
		
	ret.light[2].pos.x = 0.0;
	ret.light[2].pos.y = -5.0;
	ret.light[2].pos.z = 0.0;
	ret.light[2].col = 0xFFFF00;
	ret.light[2].type = light;
	ret.light[2].r = 35.0;
		
	ret.light[3].pos.x = 0.0;
	ret.light[3].pos.y = 5.0;
	ret.light[3].pos.z = 0.0;
	ret.light[3].col = 0xFF0000;
	ret.light[3].type = light;
	ret.light[3].r = 35.0;
		
	ret.light[4].pos.x = -5.0;
	ret.light[4].pos.y = 0.0;
	ret.light[4].pos.z = 0.0;
	ret.light[4].col = 0x00FF00;
	ret.light[4].type = light;
	ret.light[4].r = 35.0;
		
	ret.light[5].pos.x = 5.0;
	ret.light[5].pos.y = 0.0;
	ret.light[5].pos.z = 0.0;
	ret.light[5].col = 0x0000FF;
	ret.light[5].type = light;
	ret.light[5].r = 35.0;

	ret.light[6].type = end;

	ret.obj = ft_memalloc(sizeof(t_obj) * 13);

	ret.obj[0].dir.x = 0.0;
	ret.obj[0].dir.y = 0.0;
	ret.obj[0].dir.z = -1.0;
	ret.obj[0].pos.x = 0.0;
	ret.obj[0].pos.y = 0.0;
	ret.obj[0].pos.z = 15.0;
	ret.obj[0].pos.w = 0.0;
	ret.obj[0].col = 0xFFFFFF;
	ret.obj[0].n_m = 0;
	ret.obj[0].r_m = 0;
	ret.obj[0].type = plan;
	ret.obj[0].diff = 0.1;
	ret.obj[0].refl = 1.0;

	ret.obj[1].dir.x = 1.0;
	ret.obj[1].dir.y = 0.0;
	ret.obj[1].dir.z = 0.0;
	ret.obj[1].pos.x = -15.0;
	ret.obj[1].pos.y = 0.0;
	ret.obj[1].pos.z = 0.0;
	ret.obj[1].pos.w = 0.0;
	ret.obj[1].col = 0xFFFFFF;
	ret.obj[1].n_m = 0;
	ret.obj[1].r_m = 0;
	ret.obj[1].type = plan;
	ret.obj[1].diff = 0.1;
	ret.obj[1].refl = 1.0;

	ret.obj[2].dir.x = 0.0;
	ret.obj[2].dir.y = 1.0;
	ret.obj[2].dir.z = 0.0;
	ret.obj[2].pos.x = 0.0;
	ret.obj[2].pos.y = -15.0;
	ret.obj[2].pos.z = 0.0;
	ret.obj[2].pos.w = 0.0;
	ret.obj[2].col = 0xFFFFFF;
	ret.obj[2].n_m = 2;
	ret.obj[2].r_m = 3;
	ret.obj[2].tex = 4;
	ret.obj[2].type = plan;
	ret.obj[2].diff = 2.0;
	ret.obj[2].refl = 1.0;

	ret.obj[3].dir.x = 0.0;
	ret.obj[3].dir.y = -1.0;
	ret.obj[3].dir.z = 0.0;
	ret.obj[3].pos.x = 0.0;
	ret.obj[3].pos.y = 15.0;
	ret.obj[3].pos.z = 0.0;
	ret.obj[3].pos.w = 0.0;
	ret.obj[3].col = 0xFFFFFF;
	ret.obj[3].n_m = 0;
	ret.obj[3].r_m = 0;
	ret.obj[3].type = plan;
	ret.obj[3].diff = 0.1;
	ret.obj[3].refl = 1.0;

	ret.obj[4].dir.x = -1.0;
	ret.obj[4].dir.y = 0.0;
	ret.obj[4].dir.z = 0.0;
	ret.obj[4].pos.x = 15.0;
	ret.obj[4].pos.y = 0.0;
	ret.obj[4].pos.z = 0.0;
	ret.obj[4].pos.w = 0.0;
	ret.obj[4].col = 0xFFFFFF;
	ret.obj[4].n_m = 0;
	ret.obj[4].r_m = 0;
	ret.obj[4].type = plan;
	ret.obj[4].diff = 0.1;
	ret.obj[4].refl = 1.0;

	ret.obj[5].dir.x = 0.0;
	ret.obj[5].dir.y = 0.0;
	ret.obj[5].dir.z = 1.0;
	ret.obj[5].pos.x = 0.0;
	ret.obj[5].pos.y = 0.0;
	ret.obj[5].pos.z = -15.0;
	ret.obj[5].pos.w = 0.0;
	ret.obj[5].col = 0xFFFFFF;
	ret.obj[5].n_m = 0;
	ret.obj[5].r_m = 0;
	ret.obj[5].type = plan;
	ret.obj[5].diff = 0.1;
	ret.obj[5].refl = 1.0;

	ret.obj[6].pos.x = 0.0;
	ret.obj[6].pos.y = 0.0;
	ret.obj[6].pos.z = 15.0;
	ret.obj[6].pos.w = 0.0;
	ret.obj[6].col = 0xFFFFFF;
	ret.obj[6].n_m = 1;
	ret.obj[6].type = sphere;
	ret.obj[6].diff = 0.5;
	ret.obj[6].refl = 0.5;
	ret.obj[6].r = 5.0;

	ret.obj[7].pos.x = 0.0;
	ret.obj[7].pos.y = 0.0;
	ret.obj[7].pos.z = -15.0;
	ret.obj[7].pos.w = 0.0;
	ret.obj[7].col = 0xFFFFFF;
	ret.obj[7].n_m = 1;
	ret.obj[7].type = sphere;
	ret.obj[7].diff = 0.5;
	ret.obj[7].refl = 0.5;
	ret.obj[7].r = 5.0;

	ret.obj[8].pos.x = 0.0;
	ret.obj[8].pos.y = 15.0;
	ret.obj[8].pos.z = 0.0;
	ret.obj[8].pos.w = 0.0;
	ret.obj[8].col = 0xFFFFFF;
	ret.obj[8].n_m = 1;
	ret.obj[8].type = sphere;
	ret.obj[8].diff = 0.5;
	ret.obj[8].refl = 0.5;
	ret.obj[8].r = 5.0;

	ret.obj[9].pos.x = 0.0;
	ret.obj[9].pos.y = -15.0;
	ret.obj[9].pos.z = 0.0;
	ret.obj[9].pos.w = 0.0;
	ret.obj[9].col = 0xFFFFFF;
	ret.obj[9].n_m = 1;
	ret.obj[9].type = sphere;
	ret.obj[9].diff = 0.5;
	ret.obj[9].refl = 0.5;
	ret.obj[9].r = 5.0;

	ret.obj[10].pos.x = 15.0;
	ret.obj[10].pos.y = 0.0;
	ret.obj[10].pos.z = 0.0;
	ret.obj[10].pos.w = 0.0;
	ret.obj[10].col = 0xFFFFFF;
	ret.obj[10].n_m = 1;
	ret.obj[10].type = sphere;
	ret.obj[10].diff = 0.5;
	ret.obj[10].refl = 0.5;
	ret.obj[10].r = 5.0;

	ret.obj[11].pos.x = -15.0;
	ret.obj[11].pos.y = 0.0;
	ret.obj[11].pos.z = 0.0;
	ret.obj[11].pos.w = 0.0;
	ret.obj[11].col = 0xFFFFFF;
	ret.obj[11].n_m = 1;
	ret.obj[11].type = sphere;
	ret.obj[11].diff = 0.5;
	ret.obj[11].refl = 0.5;
	ret.obj[11].r = 5.0;

	ret.obj[12].type = end;
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
	return (0);
}

void	dsr(t_mlx *mlx)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	int 			y;
	int 			x;
	int				dsr_x;
	int				dsr_y;
	int				xmax;
	int				ymax;

	y = 0;
	xmax = mlx->s.cam.size.x;
	ymax = mlx->s.cam.size.y;
	while (y + 1 < ymax)
	{
		x = 0;
		while (x + 1 < xmax)
		{
			dsr_y = -1;
			r = 0;
			g = 0;
			b = 0;
			while (++dsr_y < DSR)
			{
				dsr_x = -1;
				while (++dsr_x < DSR)
				{
					r  += mlx->p[((y + dsr_y) * xmax + (x + dsr_x)) * 4 + 0];
					g  += mlx->p[((y + dsr_y) * xmax + (x + dsr_x)) * 4 + 1];
					b  += mlx->p[((y + dsr_y) * xmax + (x + dsr_x)) * 4 + 2];
				}
			}
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 0] = r / (DSR * DSR);
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 1] = g / (DSR * DSR);
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 2] = b / (DSR * DSR);
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 3] = 0;
			x += DSR;
		}
		y += DSR;
	}
}

int		ray_loop(t_mlx *mlx)
{
	int	fd;
	int i;

	if (mlx->key & (REDRAW | BSPACE))
	{
		k_apply(mlx->key, &mlx->s);
		while(++mlx->s.cam.chunk.y < mlx->s.cam.viewplane.z)
		{
			while(++mlx->s.cam.chunk.x < mlx->s.cam.viewplane.z)
			{
				ocl_enqueue_kernel(&(mlx->prog), "raytracer");
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
				mlx_do_sync(mlx->mlx);
			}
			mlx->s.cam.chunk.x = -1;
		}
		mlx->s.cam.chunk.x = -1;
		mlx->s.cam.chunk.y = -1;
		if(STEREO)
		{
			ocl_enqueue_kernel(&(mlx->prog), "cpy");
			mlx->s.cam.ori.x += 1;
			ocl_enqueue_kernel(&(mlx->prog), "raytracer");
			ocl_enqueue_kernel(&(mlx->prog), "stereo");
			mlx->s.cam.ori.x -= 1;
		}
		dsr(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		if (OUT_FILE)
		{
			fd = open("./Rendu.ppm", O_CREAT | O_TRUNC | O_WRONLY, 0775);
			ft_putnbr(fd);
			write(fd, "P6\n2560 1440\n255\n", 17);
			i = -4;
			while ((i += 4) < W * H * 4)
			{
				write(fd, &(mlx->p[i + 2]), 1);
				write(fd, &(mlx->p[i + 1]), 1);
				write(fd, &(mlx->p[i]), 1);
			}
			close(fd);
			ft_putendl("file rendered");
		}
		mlx->key -= REDRAW;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	size_t	pws[2];
	(void)ac;

	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);
	mlx.s = ft_init_scene();
	mlx.tex = get_texture(&av[1]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, W, H, "rtvocl");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.p = (unsigned char *)mlx_get_data_addr(mlx.img, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.tmp = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.atmp = mlx_get_data_addr(mlx.tmp, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.tmp2 = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.atmp2 = mlx_get_data_addr(mlx.tmp, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.s.cam.viewplane.z = 1;
	mlx.s.cam.chunk.x = -1;
	mlx.s.cam.chunk.y = -1;
	mlx.p[0] = 0;
	pws[0] = WIDTH / mlx.s.cam.viewplane.z;
	pws[1] = HEIGHT / mlx.s.cam.viewplane.z;
	mlx.key = REDRAW;
	ocl_new_kernel(&(mlx.prog), 5, pws, "norowowowowd", "raytracer", WIDTH * HEIGHT
			* sizeof(int), mlx.p, sizeof(t_cam), &(mlx.s.cam), sizeof(t_obj) * 13, 
			mlx.s.obj, sizeof(t_obj) * 7, mlx.s.light, sizeof(int) * (mlx.tex[0] + 1), mlx.tex, 2);
	ocl_new_kernel(&(mlx.prog), 3, pws, "norowowd", "cpy", WIDTH * HEIGHT
			* sizeof(int), mlx.atmp, WIDTH * HEIGHT * sizeof(int), mlx.p, sizeof(size_t) * 2, pws, 2);
	ocl_new_kernel(&(mlx.prog), 4, pws, "nowoworowd", "stereo", WIDTH * HEIGHT
			* sizeof(int), mlx.p, WIDTH * HEIGHT * sizeof(int), mlx.atmp, WIDTH * HEIGHT * sizeof(int), mlx.p,
			sizeof(size_t) * 2, pws, 2);
	mlx_hook(mlx.win, 2, (1L << 0), my_key_func, &mlx);
	mlx_hook(mlx.win, 3, (1L << 1), &k_rel, &mlx);
	mlx_loop_hook(mlx.mlx, ray_loop, &mlx);
//	ray_loop(&mlx);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
