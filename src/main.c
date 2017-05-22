#include <rt.h>

t_scene	ft_init_scene(void)
{
	t_scene	ret;

	ret.cam.ori.x = 0.0;
	ret.cam.ori.y = 0.0;
	ret.cam.ori.z = -10.0;
/* CAMERA DIRECTIONS */
	ret.cam.dirx.x = 1.0;
	ret.cam.dirx.y = 0.0;
	ret.cam.dirx.z = 0.0;

	ret.cam.diry.x = 0.0;
	ret.cam.diry.y = 1.0;
	ret.cam.diry.z = 0.0;

	ret.cam.dirz.x = 0.0;
	ret.cam.dirz.y = 0.0;
	ret.cam.dirz.z = 1.0;
/* VIEWPLANE - VIEWPORT */
	ret.cam.viewplane.x = 10.0 * ((float)W / (float)H);
	ret.cam.viewplane.y = 10.0;
	ret.cam.p.x = -5.0 * ((float)W / (float)H);
	ret.cam.p.y = 5.0;
	ret.cam.p.z = 5.0;
/* LIGHTS */
	ret.light = ft_memalloc(sizeof(t_obj) * 7);
	ret.light[0].pos.x = 9.0;
	ret.light[0].pos.y = 0.0;
	ret.light[0].pos.z = 0.0;
	ret.light[0].col = 0xFFFFFF;
	ret.light[0].type = light;
	ret.light[0].r = 50.0;

	ret.light[1].pos.x = -9.0;
	ret.light[1].pos.y = 0.0;
	ret.light[1].pos.z = 0.0;
	ret.light[1].col = 0xFFFFFF;
	ret.light[1].type = light;
	ret.light[1].r = 50.0;

	ret.light[2].pos.x = 0.0;
	ret.light[2].pos.y = 0.0;
	ret.light[2].pos.z = 9.0;
	ret.light[2].col = 0xFFFFFF;
	ret.light[2].type = light;
	ret.light[2].r = 50.0;

	ret.light[3].pos.x = 0.0;
	ret.light[3].pos.y = 0.0;
	ret.light[3].pos.z = -9.0;
	ret.light[3].col = 0xFFFFFF;
	ret.light[3].type = light;
	ret.light[3].r = 50.0;

	ret.light[4].pos.x = 0.0;
	ret.light[4].pos.y = 9.0;
	ret.light[4].pos.z = 0.0;
	ret.light[4].col = 0xFFFFFF;
	ret.light[4].type = light;
	ret.light[4].r = 50.0;

	ret.light[5].pos.x = 0.0;
	ret.light[5].pos.y = -9.0;
	ret.light[5].pos.z = 0.0;
	ret.light[5].col = 0xFFFFFF;
	ret.light[5].type = light;
	ret.light[5].r = 50.0;
	ret.light[6].type = end;
	ret.n_l = 7;
/* OBJECTS */
	ret.obj = ft_memalloc(sizeof(t_obj) * 13);
	ret.obj[0].dir.x = 0.0;
	ret.obj[0].dir.y = 0.0;
	ret.obj[0].dir.z = -1.0;
	ret.obj[0].pos.x = 0.0;
	ret.obj[0].pos.y = 0.0;
	ret.obj[0].pos.z = 15.0;
	ret.obj[0].pos.w = 0.0;
	ret.obj[0].col = 0x888888;
	ret.obj[0].n_m = 0;
	ret.obj[0].r_m = 0;
	ret.obj[0].tex = 1;
	ret.obj[0].type = plan;
	ret.obj[0].diff = 1.0;
	ret.obj[0].refl = 0.0;
	ret.obj[0].mod_tex = (cl_float4){.x = 30.0, .y = 30.0, .z = 0.0, .w = 0.0};

	ret.obj[1].dir.x = 1.0;
	ret.obj[1].dir.y = 0.0;
	ret.obj[1].dir.z = 0.0;
	ret.obj[1].pos.x = -15.0;
	ret.obj[1].pos.y = 0.0;
	ret.obj[1].pos.z = 0.0;
	ret.obj[1].pos.w = 0.0;
	ret.obj[1].col = 0x888888;
	ret.obj[1].n_m = 0;
	ret.obj[1].r_m = 0;
	ret.obj[1].tex = 1;
	ret.obj[1].type = plan;
	ret.obj[1].diff = 1.0;
	ret.obj[1].refl = 0.0;
	ret.obj[1].mod_tex = (cl_float4){.x = 30.0, .y = 30.0, .z = 0.0, .w = 0.0};

	ret.obj[2].dir.x = 0.0;
	ret.obj[2].dir.y = 1.0;
	ret.obj[2].dir.z = 0.0;
	ret.obj[2].pos.x = 0.0;
	ret.obj[2].pos.y = -15.0;
	ret.obj[2].pos.z = 0.0;
	ret.obj[2].pos.w = 0.0;
	ret.obj[2].col = 0x888888;
	ret.obj[2].n_m = 1;
	ret.obj[2].r_m = 0;
	ret.obj[2].tex = 0;
	ret.obj[2].type = plan;
	ret.obj[2].diff = 1.0;
	ret.obj[2].refl = 0.0;
	ret.obj[2].mod_tex = (cl_float4){.x = 30.0, .y = 30.0, .z = 0.0, .w = 0.0};

	ret.obj[3].dir.x = 0.0;
	ret.obj[3].dir.y = -1.0;
	ret.obj[3].dir.z = 0.0;
	ret.obj[3].pos.x = 0.0;
	ret.obj[3].pos.y = 15.0;
	ret.obj[3].pos.z = 0.0;
	ret.obj[3].pos.w = 0.0;
	ret.obj[3].col = 0x888888;
	ret.obj[3].n_m = 0;
	ret.obj[3].r_m = 0;
	ret.obj[3].tex = 1;
	ret.obj[3].type = plan;
	ret.obj[3].diff = 1.0;
	ret.obj[3].refl = 0.0;
	ret.obj[3].mod_tex = (cl_float4){.x = 30.0, .y = 30.0, .z = 0.0, .w = 0.0};

	ret.obj[4].dir.x = -1.0;
	ret.obj[4].dir.y = 0.0;
	ret.obj[4].dir.z = 0.0;
	ret.obj[4].pos.x = 15.0;
	ret.obj[4].pos.y = 0.0;
	ret.obj[4].pos.z = 0.0;
	ret.obj[4].pos.w = 0.0;
	ret.obj[4].col = 0x888888;
	ret.obj[4].n_m = 0;
	ret.obj[4].r_m = 0;
	ret.obj[4].tex = 1;
	ret.obj[4].type = plan;
	ret.obj[4].diff = 1.0;
	ret.obj[4].refl = 0.0;
	ret.obj[4].mod_tex = (cl_float4){.x = 30.0, .y = 30.0, .z = 0.0, .w = 0.0};

	ret.obj[5].dir.x = 0.0;
	ret.obj[5].dir.y = 0.0;
	ret.obj[5].dir.z = 1.0;
	ret.obj[5].pos.x = 0.0;
	ret.obj[5].pos.y = 0.0;
	ret.obj[5].pos.z = -15.0;
	ret.obj[5].pos.w = 0.0;
	ret.obj[5].col = 0x888888;
	ret.obj[5].n_m = 0;
	ret.obj[5].r_m = 0;
	ret.obj[5].tex = 1;
	ret.obj[5].type = plan;
	ret.obj[5].diff = 1.0;
	ret.obj[5].refl = 0.0;
	ret.obj[5].mod_tex = (cl_float4){.x = 30.0, .y = 30.0, .z = 0.0, .w = 0.0};

	ret.obj[6].pos.x = 0.0;
	ret.obj[6].pos.y = 0.0;
	ret.obj[6].pos.z = 0.0;
	ret.obj[6].dir.x = 0.0;
	ret.obj[6].dir.y = 1.0;
	ret.obj[6].dir.z = 0.0;
	ret.obj[6].pos.w = 0.0;
	ret.obj[6].col = 0x000000;
	ret.obj[6].r_m = 0;
	ret.obj[6].n_m = 7;
	ret.obj[6].tex = 6;
	ret.obj[6].type = cone;
	ret.obj[6].diff = 0.0;
	ret.obj[6].refl = 0.0;
	ret.obj[6].alpha = 25.0f;
	ret.obj[6].mod_tex = (cl_float4){.x = 1.0, .y = 1.0, .z = 0.0, .w = 0.0};

	ret.obj[7].pos.x = 7.5;
	ret.obj[7].pos.y = 0.0;
	ret.obj[7].pos.z = 0.0;
	ret.obj[7].dir.x = 0.0;
	ret.obj[7].dir.y = 1.0;
	ret.obj[7].dir.z = 0.0;
	ret.obj[7].pos.w = -1.0;
	ret.obj[7].col = 0xFFFFFF;
	ret.obj[7].r_m = 0;
	ret.obj[7].n_m = 7;
	ret.obj[7].tex = 6;
	ret.obj[7].type = cone;
	ret.obj[7].diff = 1.0;
	ret.obj[7].refl = 0.0;
	ret.obj[7].alpha = 25.0f;
	ret.obj[7].mod_tex = (cl_float4){.x = 1.0, .y = 1.0, .z = 0.0, .w = 0.0};

	ret.obj[8].pos.x = -7.5;
	ret.obj[8].pos.y = 0.0;
	ret.obj[8].pos.z = 0.0;
	ret.obj[8].dir.x = 0.0;
	ret.obj[8].dir.y = 1.0;
	ret.obj[8].dir.z = 0.0;
	ret.obj[8].pos.w = -1.0;
	ret.obj[8].col = 0xFFFFFF;
	ret.obj[8].r_m = 0;
	ret.obj[8].n_m = 7;
	ret.obj[8].tex = 6;
	ret.obj[8].type = cone;
	ret.obj[8].diff = 1.0;
	ret.obj[8].refl = 0.0;
	ret.obj[8].alpha = 25.0f;
	ret.obj[8].mod_tex = (cl_float4){.x = 1.0, .y = 1.0, .z = 0.0, .w = 0.0};

	ret.obj[9].pos.x = 0.0;
	ret.obj[9].pos.y = 0.0;
	ret.obj[9].pos.z = 7.5;
	ret.obj[9].dir.x = 0.0;
	ret.obj[9].dir.y = 1.0;
	ret.obj[9].dir.z = 0.0;
	ret.obj[9].pos.w = -1.0;
	ret.obj[9].col = 0xFFFFFF;
	ret.obj[9].r_m = 0;
	ret.obj[9].n_m = 7;
	ret.obj[9].tex = 6;
	ret.obj[9].type = cone;
	ret.obj[9].diff = 1.0;
	ret.obj[9].refl = 0.0;
	ret.obj[9].alpha = 25.0f;
	ret.obj[9].mod_tex = (cl_float4){.x = 1.0, .y = 1.0, .z = 0.0, .w = 0.0};

	ret.obj[10].pos.x = 0.0;
	ret.obj[10].pos.y = 0.0;
	ret.obj[10].pos.z = -7.5;
	ret.obj[10].dir.x = 0.0;
	ret.obj[10].dir.y = 1.0;
	ret.obj[10].dir.z = 0.0;
	ret.obj[10].pos.w = -1.0;
	ret.obj[10].col = 0xFFFFFF;
	ret.obj[10].r_m = 0;
	ret.obj[10].n_m = 7;
	ret.obj[10].tex = 6;
	ret.obj[10].type = cone;
	ret.obj[10].diff = 1.0;
	ret.obj[10].refl = 0.0;
	ret.obj[10].alpha = 25.0f;
	ret.obj[10].mod_tex = (cl_float4){.x = 1.0, .y = 1.0, .z = 0.0, .w = 0.0};

	ret.obj[11].pos.x = 0.0;
	ret.obj[11].pos.y = 0.0;
	ret.obj[11].pos.z = 0.0;
	ret.obj[11].dir.x = 1.0;
	ret.obj[11].dir.y = 1.0;
	ret.obj[11].dir.z = 1.0;
	ret.obj[11].pos.w = 0;
	ret.obj[11].col = 0x8F1387;
	ret.obj[11].r_m = 0;
	ret.obj[11].t_m = 2;
	ret.obj[11].n_m = 0;
	ret.obj[11].tex = 3;
	ret.obj[11].type = sphere;
	ret.obj[11].diff = 1.0;
	ret.obj[11].refl = 0.0;
	ret.obj[11].trans = 0.0;
	ret.obj[11].r = 3.0;
	ret.obj[11].mod_tex =  (cl_float4){.x = 1.0, .y = 1.0, .z = 0.0, .w = 0.0};

	ret.obj[12].type = end;
	ret.n_o = 13;
/**/
	return (ret);
}

void			exit_error(char *str)
{
	print_error(str);
	exit(0);
}

int		ray_loop(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (mlx->key & REDRAW)
	{
		k_apply(mlx->key, &mlx->s);
		while (!mlx->s.cam.fast && ++mlx->s.cam.chunk.y < mlx->s.cam.viewplane.w)
		{
			while (++mlx->s.cam.chunk.x < mlx->s.cam.viewplane.z)
			{
				if (!(ocl_enqueue_kernel(&(mlx->prog), "raytracer")))
					exit_error("Cannot full render, change your scene");
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
				mlx_do_sync(mlx->mlx);
			}
			mlx->s.cam.chunk.x = -1.0f;
		}
		if (mlx->s.cam.fast)
			if (!(ocl_enqueue_kernel(&(mlx->prog), "rt_fast")))
				exit_error("Cannot open, change your scene");
		if (!mlx->s.cam.fast && mlx->s.cam.dsr > 1)
			dsr(mlx);
		mlx->s.cam.chunk = (cl_float2){.x = -1.0f, .y = -1.0f};
		if (OUT_FILE && !mlx->s.cam.fast)
			img_file(mlx->p, mlx);
		mlx->key &= ~REDRAW;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_datawin		data;
	t_mmlx			*parent;
	static t_mlx	mlx;
	size_t			pws[2];
	size_t			pws_f[2];

	(void)ac;
	mlx.tex = get_texture(&av[1]);
	mlx.s = ft_init_scene();
	mlx.s.cam.dsr = 1;
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000, &(mlx.prog))))
		return (0);
	mlx.mlx = mlx_init();
	rt_win_redraw(&mlx.key);
	data = (t_datawin){.name = "rtvocl",\
			.xwin = W, .ywin = H,\
			.f_keypress = k_press, .data_kp = &mlx,\
			.f_mousepress = m_press, .data_mp = &mlx,\
			.f_keyrelease = k_rel, .data_kr = &mlx,\
			.f_loop = ray_loop, .data_lp = &mlx};
	parent = mmlx_create_parent(mlx.mlx, &data);
	mlx.win = parent->win;
	mlx.parent = parent;
	if (mlx.s.cam.dsr > 1)
	{
		mlx_destroy_image(parent->mlx, parent->img);
		parent->img = mlx_new_image(parent->mlx, WIDTH, HEIGHT);
		parent->data = mlx_get_data_addr(parent->img, &mlx.bp, &mlx.sl, &mlx.endian);
	}
	mlx.img = parent->img;
	mlx.p = (unsigned char*)parent->data;
	mlx.tmp = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.tmp2 = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.atmp = mlx_get_data_addr(mlx.tmp, &mlx.bp, &mlx.sl, &mlx.endian);
	mlx.atmp2 = mlx_get_data_addr(mlx.tmp2, &mlx.bp, &mlx.sl, &mlx.endian);
	mlx.s.cam.chunk = (cl_float2){.x = -1, .y = -1};
	mlx.s.cam.size = (cl_int2){.x = WIDTH, .y = HEIGHT};
	mlx.s.cam.ambient = 0x252525;
	mlx.s.cam.viewplane.z = 2;
	mlx.s.cam.viewplane.w = 2;
	pws[0] = WIDTH / mlx.s.cam.viewplane.z;
	pws[1] = HEIGHT / mlx.s.cam.viewplane.w;
	pws_f[0] = W / 2;
	pws_f[1] = H / 2;
	mlx.key = REDRAW;
	ocl_new_kernel(&(mlx.prog), 5, pws, "norowowowowd", "raytracer",\
			sizeof(int) * WIDTH * HEIGHT, mlx.p,\
			sizeof(t_cam), &(mlx.s.cam),\
			sizeof(t_obj) * mlx.s.n_o, mlx.s.obj,\
			sizeof(t_obj) * mlx.s.n_l, mlx.s.light,\
			sizeof(int) * (mlx.tex[0] + 1), mlx.tex, 2);
	ocl_new_kernel(&(mlx.prog), 5, pws_f, "norowowoword", "rt_fast",\
			sizeof(int) * WIDTH * HEIGHT, mlx.p,\
			sizeof(t_cam), &(mlx.s.cam),\
			sizeof(t_obj) * mlx.s.n_o, mlx.s.obj,\
			sizeof(int) * 2, &mlx.mouse,\
			sizeof(int), &mlx.oid, 2);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
