#include <rt.h>

void	img_file(unsigned char *img)
{
	time_t	t;
	char	*name;
	int		fd;
	int		x;
	int		y;

	t = time(NULL);
	name = ft_strjoin(ctime(&t), "_rt.ppm");
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0775);
	ft_putstr_fd("P6\n", fd);
	ft_putstr_fd(ft_itoa(W), fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(ft_itoa(H), fd);
	ft_putstr_fd("\n255\n", fd);
	y = -1;
	print_info(name);
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			write(fd, &(img[(y * WIDTH + x) * 4 + 2]), 1);
			write(fd, &(img[(y * WIDTH + x) * 4 + 1]), 1);
			write(fd, &(img[(y * WIDTH + x) * 4]), 1);
		}
	}
	close(fd);
	ft_putendl("File Rendered.");
}

void	dsr(t_mlx *mlx)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	int				y;
	int				x;
	int				dsr_x;
	int				dsr_y;
	int				xmax;
	int				ymax;

	xmax = mlx->s.cam.size.x;
	ymax = mlx->s.cam.size.y;
	y = -DSR;
	while ((y += DSR) + 1 < ymax)
	{
		x = -DSR;
		while ((x += DSR) + 1 < xmax)
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
					r += mlx->p[((y + dsr_y) * xmax + (x + dsr_x)) * 4 + 2];
					g += mlx->p[((y + dsr_y) * xmax + (x + dsr_x)) * 4 + 1];
					b += mlx->p[((y + dsr_y) * xmax + (x + dsr_x)) * 4 + 0];
				}
			}
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 0] = b / (DSR * DSR);
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 1] = g / (DSR * DSR);
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 2] = r / (DSR * DSR);
			mlx->p[(y / DSR * xmax + x / DSR) * 4 + 3] = 0;
		}
	}
}

int		ray_loop(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (mlx->key & REDRAW)
	{
		k_apply(mlx->key, &mlx->s);
		while(!mlx->s.cam.fast && ++mlx->s.cam.chunk.y < mlx->s.cam.viewplane.w)
		{
			while(++mlx->s.cam.chunk.x < mlx->s.cam.viewplane.z)
			{
				if(!(ocl_enqueue_kernel(&(mlx->prog), "raytracer")))
					exit_error("Cannot full render, chnge your scene");
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
				mlx_do_sync(mlx->mlx);
			}
			mlx->s.cam.chunk.x = -1.0f;
		}
		if(mlx->s.cam.fast)
			if(!(ocl_enqueue_kernel(&(mlx->prog), "rt_fast")))
				exit_error("Cannot open, chnge your scene");
		if(!mlx->s.cam.fast && DSR > 1)
			dsr(mlx);
		mlx->s.cam.chunk = (cl_float2){.x = -1.0f, .y = -1.0f};
		if(STEREO)
		{
			ocl_enqueue_kernel(&(mlx->prog), "cpy");
			++mlx->s.cam.ori.x;
			ocl_enqueue_kernel(&(mlx->prog), "raytracer");
			ocl_enqueue_kernel(&(mlx->prog), "stereo");
			--mlx->s.cam.ori.x;
		}
		if (OUT_FILE && !mlx->s.cam.fast)
			img_file(mlx->p);
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
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);
	mlx.mlx = mlx_init();
	rt_win_redraw(&mlx.key);
	data = (t_datawin){.name = "rtvocl", .xwin = W, .ywin = H,\
			.f_keypress = k_press, .data_kp = &mlx,\
			.f_mousepress = m_press, .data_mp = &mlx,\
			.f_keyrelease = k_rel, .data_kr = &mlx,\
			.f_loop = ray_loop, .data_lp = &mlx};
	parent = mmlx_create_parent(mlx.mlx, &data);
	mlx.win = parent->win;
	mlx.parent = parent;
	if (DSR > 1)
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
<<<<<<< HEAD
	mlx.s.cam.viewplane.z = 4;
=======
	mlx.s.cam.viewplane.z = 2;
	mlx.s.cam.viewplane.w = 4;
>>>>>>> 6fc8fe632d54a33bc08c9f06f361442beb25d613
	mlx.s.cam.chunk.x = -1;
	mlx.s.cam.chunk.y = -1;
	mlx.s.cam.dsr = DSR;
	mlx.s.cam.size.x = WIDTH;
	mlx.s.cam.size.y = HEIGHT;
	mlx.s.cam.ambient = 0x901010;
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
	ocl_new_kernel(&(mlx.prog), 3, pws, "norowowd", "cpy",\
			sizeof(int) * WIDTH * HEIGHT, mlx.atmp,\
			sizeof(int) * WIDTH * HEIGHT, mlx.p,\
			sizeof(size_t) * 2, pws, 2);
	ocl_new_kernel(&(mlx.prog), 4, pws, "nowoworowd", "stereo",\
			sizeof(int) * WIDTH * HEIGHT, mlx.p,\
			sizeof(int) * WIDTH * HEIGHT, mlx.atmp,\
			sizeof(int) * WIDTH * HEIGHT, mlx.p,
			sizeof(size_t) * 2, pws, 2);
	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
