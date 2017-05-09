/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 21:19:17 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/09 16:49:04 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#include <rt.h>

void	img_file(unsigned char *img, char *name, t_data *d)
{
	int fd;
	int	i;

	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0775);

	ft_putstr_fd("P6\n", fd);
	ft_putstr_fd(ft_itoa(d->width), fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(ft_itoa(d->height), fd);
	ft_putstr_fd("\n255\n", fd);
	i = -4;
	while ((i += 4) < d->width * d->height * 4)
	{
		write(fd, &(img[i + 2]), 1);
		write(fd, &(img[i + 1]), 1);
		write(fd, &(img[i]), 1);
	}
	close(fd);
	print_info("file rendered");
	exit(0);
}

void	render(t_data *d, t_ocl_prog *prog)
{
	//while(++d->cam.chunk.y < d->line + d->height)
	//{
	//	d->cam.chunk.x = -1;
	//	while(++d->cam.chunk.x < d->scale)
			ocl_enqueue_kernel(prog, "raytracer");
	//}
	img_file(d->img, "rendu.ppm", d);
}

t_data	str_to_data(unsigned char *str)
{
	t_data	data;

	data = *(t_data *)ft_memalloc(sizeof(t_data));
	data.size = *(int *)(&str[0]);
	data.n_t = *(int *)(&str[4]);
	data.n_o = *(int *)(&str[8]);
	data.n_l = *(int *)(&str[12]);
	data.tex = (int *)ft_memalloc(sizeof(int) * data.n_t);
	ft_memcpy(data.tex, &str[16], sizeof(int) * data.n_t);
	ft_memcpy(&data.cam, &str[16 + sizeof(int) * data.n_t], sizeof(t_cam));
	data.obj = (t_obj *)ft_memalloc(sizeof(t_obj) * data.n_o);
	ft_memcpy(data.obj, &str[16 + sizeof(int) * data.n_t + sizeof(t_cam)] , sizeof(t_obj) * data.n_o);
	data.light = (t_obj *)ft_memalloc(sizeof(t_obj) * data.n_l);
	ft_memcpy(data.light, &str[16 + sizeof(int) * data.n_t + sizeof(t_cam) + sizeof(t_obj) * data.n_o], sizeof(t_obj) * data.n_l);
	return (data);
}

void callback_init(t_client *c)
{
	t_ocl_prog	prog;
	t_data		d;
	size_t		pws[2];

	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &prog)))
		exit(-1);
	d = str_to_data(c->buf);
	d.width = 1280;
	d.height = 720;
	d.scale = 1;
	d.line = 1;
	d.cam.chunk.y = 0;//d.line - 1;
	d.cam.chunk.x = 0;
	d.cam.viewplane.z = d.scale;
	d.img = (unsigned char *)ft_memalloc(d.width * d.height * sizeof(int));
	pws[0] = d.width/* / d.scale*/;
	pws[1] = d.height;
	ocl_new_kernel(&prog, 5, pws, "norowowowowd", "raytracer", \
			sizeof(int) * d.width * d.height, d.img, \
			sizeof(t_cam), &(d.cam), \
			sizeof(t_obj) * d.n_o, d.obj, \
			sizeof(t_obj) * d.n_l, d.light, \
			sizeof(int) * (d.tex[0] + 1), d.tex, 2);
	render(&d, &prog);
	ocl_finish(prog);
}
