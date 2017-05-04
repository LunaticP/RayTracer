/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/04 22:47:29 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rt_network.h>

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
	ft_putendl("file rendered");
}

void	render(t_data *d, t_ocl_prog *prog)
{
	while(++d->s.cam.chunk.y < d->line + d->height)
	{
		d->s.cam.chunk.x = -1;
		while(++d->s.cam.chunk.x < d->scale)
			ocl_enqueue_kernel(prog, "raytracer");
	}
}

int		main(int ac, char **av)
{
	t_ocl_prog		prog;
	t_data			d;
	size_t			pws[2];
	unsigned char	*img;

	if (ac != 2)
		error_code(err_arg);
	init_network(av[1]);
	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &prog)))
		return (0);
//	d.s.cam.chunk.y = d.line - 1;
//	d.s.cam.viewplane.z = d.scale;
//	img = (unsigned char *)ft_memalloc(d.width * d.height * 4);
//	pws[0] = d.width / d.scale;//BUG: floating point exeption
//	pws[1] = d.height;
//	ocl_new_kernel(&prog, 5, pws, "norowowowowd", "raytracer", \
//			sizeof(int) * d.width * d.height, img, \
//			sizeof(t_cam), &(d.s.cam), \
//			sizeof(t_obj) * d.s.n_o, d.s.obj, \
//			sizeof(t_obj) * d.s.n_l, d.s.light, \
//			sizeof(int) * (d.tex[0] + 1), d.tex, 2);
//	render(&d, &prog);
//	img_file(img, (char *)"out.ppm", &d);
//	ocl_finish(prog);

	while (1)
		;//Infinite loop for wait server thread
	return (0);
}
