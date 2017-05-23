#include <rt.h>

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
					exit_error("Cannot full render, chnge your scene");
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
				mlx_do_sync(mlx->mlx);
			}
			mlx->s.cam.chunk.x = -1.0f;
		}
		if (mlx->s.cam.fast)
			if (!(ocl_enqueue_kernel(&(mlx->prog), "rt_fast")))
				exit_error("Cannot open, chnge your scene");
		if (!mlx->s.cam.fast && mlx->DSR > 1)
			dsr(mlx);
		mlx->s.cam.chunk = (cl_float2){.x = -1.0f, .y = -1.0f};
		if (OUT_FILE && !mlx->s.cam.fast)
			img_file(mlx);
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
	mlx = rt_get_parser(av[1], mlx);
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000, &(mlx.prog))))
		return (0);
	mlx.mlx = mlx_init();
	rt_win_redraw(&mlx.key);
	data = (t_datawin){.name = "rtvocl", .xwin = mlx.W, .ywin = mlx.H,\
			.f_keypress = k_press, .data_kp = &mlx,\
			.f_mousepress = m_press, .data_mp = &mlx,\
			.f_keyrelease = k_rel, .data_kr = &mlx,\
			.f_loop = ray_loop, .data_lp = &mlx};
	parent = mmlx_create_parent(mlx.mlx, &data);
	mlx.win = parent->win;
	mlx.parent = parent;
	if (mlx.DSR > 1)
	{
		mlx_destroy_image(parent->mlx, parent->img);
		parent->img = mlx_new_image(parent->mlx, mlx.WIDTH, mlx.HEIGHT);
		parent->data = mlx_get_data_addr(parent->img, &mlx.bp, &mlx.sl, &mlx.endian);
	}
	mlx.img = parent->img;
	mlx.p = (unsigned char*)parent->data;
	mlx.s.cam.chunk = (cl_float2){.x = -1, .y = -1};
	mlx.s.cam.size = (cl_int2){.x = mlx.WIDTH, .y = mlx.HEIGHT};
	rot_cam(&mlx.s.cam, mlx.s.cam.diry, mlx.s.cam.rot.x);
	rot_cam(&mlx.s.cam, mlx.s.cam.dirx, mlx.s.cam.rot.y);
	rot_cam(&mlx.s.cam, mlx.s.cam.dirz, mlx.s.cam.rot.z);
	mlx.s.cam.ambient = 0;
	pws[0] = mlx.WIDTH / mlx.s.cam.viewplane.z;
	pws[1] = mlx.HEIGHT / mlx.s.cam.viewplane.w;
	pws_f[0] = mlx.W / 2;
	pws_f[1] = mlx.H / 2;
	mlx.key = REDRAW;
	ocl_new_kernel(&(mlx.prog), 5, pws, "norowowowowd", "raytracer",\
			sizeof(int) * mlx.WIDTH * mlx.HEIGHT, mlx.p,\
			sizeof(t_cam), &(mlx.s.cam),\
			sizeof(t_obj) * mlx.s.n_o, mlx.s.obj,\
			sizeof(t_obj) * mlx.s.n_l, mlx.s.light,\
			sizeof(int) * (mlx.tex[0] + 1), mlx.tex, 2);
	ocl_new_kernel(&(mlx.prog), 5, pws_f, "norowowoword", "rt_fast",\
			sizeof(int) * mlx.WIDTH * mlx.HEIGHT, mlx.p,\
			sizeof(t_cam), &(mlx.s.cam),\
			sizeof(t_obj) * mlx.s.n_o, mlx.s.obj,\
			sizeof(int) * 2, &mlx.mouse,\
			sizeof(int), &mlx.oid, 2);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
