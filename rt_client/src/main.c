/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 01:37:39 by jplevy            #+#    #+#             */
/*   Updated: 2017/05/09 00:29:21 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rt_network.h>

t_ocl_prog	*save_prog(int status, t_ocl_prog *prog)
{
	static t_ocl_prog *saved = NULL;

	if (status)
		saved = prog;
	return (saved);
}

int		main(int ac, char **av)
{
//	t_ocl_prog		prog;

	if (ac != 2)
		error_code(err_arg);
	init_network(av[1]);
	//d = str_to_data(??);
//	if (!(ocl_new_prog("./cl_src/rt.cl", 0x1000000 , &prog)))
//		return (0);
//	save_prog(1, &prog);

//	render(&d, &prog);
//	img_file(img, (char *)"out.ppm", &d);
//	ocl_finish(prog);
	while (1)
		;//Infinite loop for wait server thread
	return (0);
}
