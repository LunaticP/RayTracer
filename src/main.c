/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/04/18 16:07:14 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
# define STEREO 0
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
	ret.cam.ori.y = 10.0;
	ret.cam.ori.z = -18.5;

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
	ret.cam.p.z = 2.0;

	ret.light = ft_memalloc(sizeof(t_obj) * 3);
	ret.light[0].pos.x = -40.0;
	ret.light[0].pos.y = 40.0;
	ret.light[0].pos.z = -40.0;

	ret.light[0].col = 0xFFFFFF;
	ret.light[0].type = light;
	ret.light[0].r = 1700.0;

	ret.light[1].pos.x = 40.0;
	ret.light[1].pos.y = 40.0;
	ret.light[1].pos.z = -40.0;

	ret.light[1].col = 0xFFFFFF;
	ret.light[1].type = light;
	ret.light[1].r = 1700.0;
/*
	ret.light[2].pos.x = 0.0;
	ret.light[2].pos.y = 25.0;
	ret.light[2].pos.z = 0.0;

	ret.light[2].col = 0xFFFFFF;
	ret.light[2].type = light;
	ret.light[2].r = 100.0;

	ret.light[3].pos.x = 0.0;
	ret.light[3].pos.y = 20.0;
	ret.light[3].pos.z = 20.0;

	ret.light[3].col = 0xFFFFFF;
	ret.light[3].type = light;
	ret.light[3].r = 250.0;
*/
	ret.light[2].type = end;

	ret.obj = (t_obj *)ft_memalloc(sizeof(t_obj) * 18);

	ret.obj[0].pos.x = -12.0;
	ret.obj[0].pos.y = 0.0;
	ret.obj[0].pos.z = 12.0;

	ret.obj[0].col = 0xFF902C;
	ret.obj[0].type = cylindre;
	ret.obj[0].r = 5;
	ret.obj[0].dir.x = -1;
	ret.obj[0].dir.y = 1;
	ret.obj[0].dir.z = 1;
	ret.obj[0].dir = vec_norm(ret.obj[7].dir);

	vec_to_polar(&(ret.obj[7].tet), &(ret.obj[7].phi), ret.obj[7].dir);

	ret.obj[0].diff = 1;
	ret.obj[0].trans = 0;
	ret.obj[0].refl = 0;

	ret.obj[1].dir.x = 0.5;
	ret.obj[1].dir.y = 1.0;
	ret.obj[1].dir.z = 0.0;
	ret.obj[1].pos.x = -6.0;
	ret.obj[1].pos.y = 5.0;
	ret.obj[1].pos.z = 7.0;

	ret.obj[1].col = 0xC62731;
	ret.obj[1].type = cone;
	ret.obj[1].alpha = 30.0;
	ret.obj[1].diff = 1;
	ret.obj[1].trans = 0;
	ret.obj[1].refl = 0;
//	ret.obj[1].trans = 3;

	ret.obj[2].pos.x = 0.0;
	ret.obj[2].pos.y = 0.0;
	ret.obj[2].pos.z = 0.0;
	ret.obj[2].dir.x = 0.0;
	ret.obj[2].dir.y = 1.0;
	ret.obj[2].dir.z = 0.0;

	ret.obj[2].col = 0x9D1724;
	ret.obj[2].type = sphere;
	ret.obj[2].r = 3;
	ret.obj[2].trans = 0.3;
	ret.obj[2].diff = 0.7;
	ret.obj[2].refl = 0;
//	ret.obj[2].trans = 3;

	ret.obj[3].pos.x = 12.0;
	ret.obj[3].pos.y = 0.0;
	ret.obj[3].pos.z = -8.0;

	ret.obj[3].col = 0x2C934B;
	ret.obj[3].type = sphere;
	ret.obj[3].r = 3;
	ret.obj[3].trans = 0.0;
	ret.obj[3].diff = 0.99;
	ret.obj[3].refl = 0.01;
//	ret.obj[3].trans = 3;

	ret.obj[4].pos.x = 12.0;
	ret.obj[4].pos.y = 0.0;
	ret.obj[4].pos.z = 0.0;
	ret.obj[4].trans = 0.0;
	ret.obj[4].diff = 1.0;
	ret.obj[4].refl = 1.0;

	ret.obj[4].col = 0xFFFFFF;
	ret.obj[4].type = sphere;
	ret.obj[4].r = 3;

	ret.obj[5].pos.x = -3.0;
	ret.obj[5].pos.y = 0.0;
	ret.obj[5].pos.z = 5.0;
	ret.obj[5].trans = 0.3;
	ret.obj[5].diff = 0.7;
	ret.obj[5].refl = 0;
//	ret.obj[5].trans = 3;

	ret.obj[5].col = 0x0450D5;
	ret.obj[5].type = sphere;
	ret.obj[5].r = 3;

	ret.obj[6].pos.x = -9.0;
	ret.obj[6].pos.y = 0.0;
	ret.obj[6].pos.z = 5.0;
	ret.obj[6].diff = 1.0;
	ret.obj[6].trans = 0;
	ret.obj[6].refl = 0.5;
//	ret.obj[6].trans = 3;

	ret.obj[6].col = 0x8D3AA0;
	ret.obj[6].type = sphere;
	ret.obj[6].r = 3;

	ret.obj[7].pos.x = 3.0;
	ret.obj[7].pos.y = 0.0;
	ret.obj[7].pos.z = 5.0;
	ret.obj[7].diff = 1;
	ret.obj[7].trans = 0;
	ret.obj[7].refl = 0;
//	ret.obj[7].trans = 3;

	ret.obj[7].col = 0xE8AA02;
	ret.obj[7].type = sphere;
	ret.obj[7].r = 3;

	ret.obj[8].pos.x = 9.0;
	ret.obj[8].pos.y = 0.0;
	ret.obj[8].pos.z = 5.0;
	ret.obj[8].diff = 1;
	ret.obj[8].trans = 0;
	ret.obj[8].refl = 0;

	ret.obj[8].col = 0;
	ret.obj[8].type = sphere;
	ret.obj[8].r = 3;

	ret.obj[9].pos.x = -6.0;
	ret.obj[9].pos.y = 0.0;
	ret.obj[9].pos.z = 10.0;
	ret.obj[9].diff = 1;
	ret.obj[9].trans = 0;

	ret.obj[9].col = 0x165BD9;
	ret.obj[9].refl = 0;
	ret.obj[9].type = sphere;
	ret.obj[9].r = 3;
///////////////////////////////
	ret.obj[10].dir.x = 0.0;
	ret.obj[10].dir.y = 1.0;
	ret.obj[10].dir.z = 0.0;
	ret.obj[10].pos.x = 5.0;
	ret.obj[10].pos.y = 10.0;
	ret.obj[10].pos.z = 10.0;
	ret.obj[10].trans = 0.2;
	ret.obj[10].diff = 0.9;
	ret.obj[10].refl = 0.2;

	ret.obj[10].col = 0xE1352D;
	ret.obj[10].type = para;
	ret.obj[10].r = 2;
//////////////////////////////
	ret.obj[11].pos.x = 6.0;
	ret.obj[11].pos.y = 0.0;
	ret.obj[11].pos.z = 10.0;
	ret.obj[11].diff = 1;
	ret.obj[11].trans = 0;
	ret.obj[11].refl = 0;

	ret.obj[11].col = 0x912335;
	ret.obj[11].type = sphere;
	ret.obj[11].r = 3;

	ret.obj[12].pos.x = -3.0;
	ret.obj[12].pos.y = 0.0;
	ret.obj[12].pos.z = 15.0;

	ret.obj[12].col = 0xFCE704;
	ret.obj[12].type = sphere;
	ret.obj[12].r = 3;
	ret.obj[12].diff = 1;
	ret.obj[12].trans = 0;
	ret.obj[12].refl = 0;

	ret.obj[13].pos.x = 3.0;
	ret.obj[13].pos.y = 0.0;
	ret.obj[13].pos.z = 15.0;
	ret.obj[13].diff = 1;
	ret.obj[13].trans = 0;
	ret.obj[13].refl = 0;

	ret.obj[13].col = 0x702E6F;
	ret.obj[13].type = sphere;
	ret.obj[13].r = 3;

	ret.obj[14].pos.x = 0.0;
	ret.obj[14].pos.y = 0.0;
	ret.obj[14].pos.z = 20.0;

	ret.obj[14].col = 0xFC7C1B;
	ret.obj[14].type = sphere;
	ret.obj[14].r = 3;
	ret.obj[14].diff = 1;
	ret.obj[14].trans = 0;
	ret.obj[14].refl = 0;

	ret.obj[15].dir.x = 0.0;
	ret.obj[15].dir.y = 1.0;
	ret.obj[15].dir.z = 0.0;
	ret.obj[15].pos.x = 0.0;
	ret.obj[15].pos.y = -3.0;
	ret.obj[15].pos.z = 0.0;
	ret.obj[15].diff = 1.0;
	ret.obj[15].trans = 0;
	ret.obj[15].refl = 1.0;

	ret.obj[15].col = 0xCCCCCC;
	ret.obj[15].type = plan;

	ret.obj[16].dir.x = 0.0;
	ret.obj[16].dir.y = 0.0;
	ret.obj[16].dir.z = -1.0;
	ret.obj[16].pos.x = 0.0;
	ret.obj[16].pos.y = 0.0;
	ret.obj[16].pos.z = 50.0;
	ret.obj[16].diff = 1;
	ret.obj[16].trans = 0;
	ret.obj[16].refl = 0;
//	ret.obj[16].diff = 1.0;
//	ret.obj[16].ref = 0.0;

	ret.obj[16].col = 0xCCCCCC;
	ret.obj[16].type = plan;

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
	int 	y;
	int 	x;
	int		r;
	int		g;
	int		b;
	int		xmax;
	int		ymax;

	y = 0;
	xmax = mlx->s.cam.size.x;
	ymax = mlx->s.cam.size.y;
	while (y <= ymax)
	{
		x = 0;
		while (x <= xmax)
		{
			r  = mlx->p[((y + 0) * xmax + (x + 0)) * 4 + 0];
			r += mlx->p[((y + 0) * xmax + (x + 1)) * 4 + 0];
	  		r += mlx->p[((y + 1) * xmax + (x + 0)) * 4 + 0];
			r += mlx->p[((y + 1) * xmax + (x + 1)) * 4 + 0];
	  		g  = mlx->p[((y + 0) * xmax + (x + 0)) * 4 + 1];
			g += mlx->p[((y + 0) * xmax + (x + 1)) * 4 + 1];
	  		g += mlx->p[((y + 1) * xmax + (x + 0)) * 4 + 1];
			g += mlx->p[((y + 1) * xmax + (x + 1)) * 4 + 1];
  			b  = mlx->p[((y + 0) * xmax + (x + 0)) * 4 + 2];
			b += mlx->p[((y + 0) * xmax + (x + 1)) * 4 + 2];
  			b += mlx->p[((y + 1) * xmax + (x + 0)) * 4 + 2];
			b += mlx->p[((y + 1) * xmax + (x + 1)) * 4 + 2];
			mlx->p[(y / 2 * xmax + x / 2) * 4 + 0] = (unsigned char)(r / 4);
			mlx->p[(y / 2 * xmax + x / 2) * 4 + 1] = (unsigned char)(g / 4);
			mlx->p[(y / 2 * xmax + x / 2) * 4 + 2] = (unsigned char)(b / 4);
			mlx->p[(y / 2 * xmax + x / 2) * 4 + 3] = 0;

			x += 2;
		}
		y += 2;
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
		if(STEREO)
		{
			ocl_enqueue_kernel(&(mlx->prog), "cpy");
			mlx->s.cam.ori.x += 1;
			ocl_enqueue_kernel(&(mlx->prog), "raytracer");
			ocl_enqueue_kernel(&(mlx->prog), "stereo");
			mlx->s.cam.ori.x -= 1;
		}
//		ocl_enqueue_kernel(&(mlx->prog), "rng");
//		ocl_enqueue_kernel(&(mlx->prog), "cpy");
//		if(mlx->key & BSPACE)
//		ocl_enqueue_kernel(&(mlx->prog), "rng");
//		else
//		ocl_enqueue_kernel(&(mlx->prog), "raytracer");
//		ocl_enqueue_kernel(dof, "rng");
//		dsr(mlx);
//		if(mlx->key & BSPACE)
//		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->tmp, 0, 0);
//		else
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
//		bzero(mlx->p, WIDTH * HEIGHT);
		mlx->key -= REDRAW;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	size_t	pws[2];
//	int		dst = 25;
//	cl_int[2] = {3, 3};
//	cl_float filter[9]= {}
	mlx.tex = malloc(sizeof(int) * 5);
	mlx.tex[0] = 5;
	mlx.tex[1] = 0xFFFFFF;
	mlx.tex[2] = 0xFF0000;
	mlx.tex[3] = 0x00FF00;
	mlx.tex[4] = 0x0000FF;
	if (ac != 1 || !(av))
		return (0);
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);
	mlx.s = ft_init_scene();
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "rtvocl");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.p = mlx_get_data_addr(mlx.img, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.tmp = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.atmp = mlx_get_data_addr(mlx.tmp, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.tmp2 = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.atmp2 = mlx_get_data_addr(mlx.tmp, &(mlx.bp), &(mlx.sl), &(mlx.endian));
	mlx.p[0] = 0;
	mlx.key = REDRAW;
	pws[0] = WIDTH;
	pws[1] = HEIGHT;
	ocl_new_kernel(&(mlx.prog), 5, pws, "norowowowowd", "raytracer", WIDTH * HEIGHT
			* sizeof(int), mlx.p, sizeof(t_cam), &(mlx.s.cam), sizeof(t_obj) * 18, 
			mlx.s.obj, sizeof(t_obj) * 3, mlx.s.light, sizeof(int) * (mlx.tex[0] + 1), mlx.tex, 2);

//	ocl_new_kernel(&(mlx.prog), 5, pws, "nowowowoword", "rng", WIDTH * HEIGHT
//			* sizeof(int), mlx.p, sizeof(t_cam), &(mlx.s.cam), sizeof(t_obj) * 18, 
//			mlx.s.obj, sizeof(int), &dst, sizeof(int) * WIDTH * HEIGHT, mlx.atmp, 2);
	ocl_new_kernel(&(mlx.prog), 3, pws, "norowowd", "cpy", WIDTH * HEIGHT
			* sizeof(int), mlx.atmp, WIDTH * HEIGHT * sizeof(int), mlx.p, sizeof(size_t) * 2, pws, 2);
	ocl_new_kernel(&(mlx.prog), 4, pws, "nowoworowd", "stereo", WIDTH * HEIGHT
			* sizeof(int), mlx.p, WIDTH * HEIGHT * sizeof(int), mlx.atmp, WIDTH * HEIGHT * sizeof(int), mlx.p,
			sizeof(size_t) * 2, pws, 2);

	mlx_hook(mlx.win, 2, (1L << 0), my_key_func, &mlx);
	mlx_hook(mlx.win, 3, (1L << 1), &k_rel, &mlx);
	mlx_loop_hook(mlx.mlx, ray_loop, &mlx);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
