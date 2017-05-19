#include <rt.h>

cl_float4		vec_norm(cl_float4 vec)
{
	cl_float4	norm;
	float		lenght;

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

void	img_file(unsigned char *img)
{
	time_t	t;
	char	*name;
	int		fd;
	int		i;

	t = time(NULL);
	name = ft_strjoin(ctime(&t), ".ppm");
	ft_putendl(name);
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0775);
	ft_putstr_fd("P6\n", fd);
	ft_putstr_fd(ft_itoa(W), fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(ft_itoa(H), fd);
	ft_putstr_fd("\n255\n", fd);
	i = -4;
	while ((i += 4) < W * H * 4)
	{
		write(fd, &(img[i + 2]), 1);
		write(fd, &(img[i + 1]), 1);
		write(fd, &(img[i]), 1);
	}
	close(fd);
	ft_putendl("File Rendered.");
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
		while(!mlx->s.cam.fast && ++mlx->s.cam.chunk.y < mlx->s.cam.viewplane.z)
		{
			while(++mlx->s.cam.chunk.x < mlx->s.cam.viewplane.z)
			{
				ocl_enqueue_kernel(&(mlx->prog), "raytracer");
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
				mlx_do_sync(mlx->mlx);
			}
			mlx->s.cam.chunk.x = -1.0f;
		}
		if(mlx->s.cam.fast)
			ocl_enqueue_kernel(&(mlx->prog), "rt_fast");
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
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		if (OUT_FILE && !mlx->s.cam.fast)
			img_file(mlx->p);
		mlx->key &= ~REDRAW;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_datawin	data;
	t_mmlx		*parent;
	static t_mlx	mlx;
	size_t			pws[2];
	size_t			pws_f[2];
	(void)ac;

	mlx = rt_get_parser(av[1], mlx); // mlx tex, return struct mlx

	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &(mlx.prog))))
		return (0);

	mlx.mlx = mlx_init();
	rt_win_redraw(&mlx.key);

	data = (t_datawin){.name = "rtvocl", .xwin = W, .ywin = H,
			.f_keypress = k_press, .data_kp = &mlx,
			.f_mousepress = m_press, .data_mp = &mlx,
			.f_keyrelease = k_rel, .data_kr = &mlx,
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

	mlx.s.cam.viewplane.z = 1;
	mlx.s.cam.chunk.x = -1;
	mlx.s.cam.chunk.y = -1;
	mlx.s.cam.dsr = 1;
//	mlx.p[0] = 0;
	pws[0] = WIDTH / mlx.s.cam.viewplane.z;
	pws[1] = HEIGHT / mlx.s.cam.viewplane.z;
	pws_f[0] = W / 2;
	pws_f[1] = H / 2;
	mlx.key = REDRAW;
	ocl_new_kernel(&(mlx.prog), 5, pws, "norowowowowd", "raytracer", WIDTH * HEIGHT
			* sizeof(int), mlx.p, sizeof(t_cam),
			&(mlx.s.cam), sizeof(t_obj) * mlx.s.n_o,
			mlx.s.obj,
			sizeof(t_obj) * mlx.s.n_l,
			mlx.s.light, sizeof(int) * (mlx.tex[0] + 1),
			mlx.tex, 2);
	ocl_new_kernel(&(mlx.prog), 5, pws_f, "norowowoword", "rt_fast", WIDTH * HEIGHT
			* sizeof(int), mlx.p, sizeof(t_cam), &(mlx.s.cam),
			sizeof(t_obj) * mlx.s.n_o, mlx.s.obj, sizeof(int) * 2, &mlx.mouse
			, sizeof(int), &mlx.oid, 2);
	ocl_new_kernel(&(mlx.prog), 3, pws, "norowowd", "cpy", WIDTH * HEIGHT
			* sizeof(int), mlx.atmp, WIDTH * HEIGHT * sizeof(int), mlx.p, sizeof(size_t) * 2, pws, 2);
	ocl_new_kernel(&(mlx.prog), 4, pws, "nowoworowd", "stereo", WIDTH * HEIGHT
			* sizeof(int), mlx.p, WIDTH * HEIGHT * sizeof(int), mlx.atmp, WIDTH * HEIGHT * sizeof(int), mlx.p,
			sizeof(size_t) * 2, pws, 2);


	mlx_loop(mlx.mlx);
	ocl_finish(mlx.prog);
	return (0);
}
