/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_build_prog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 04:33:10 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/04 04:37:51 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_build_prog(char *filename, size_t max_src_size, t_ocl_prog *p)
{
	char		*src_str;
	size_t		src_size;
	int			fd;
	cl_int		ret;

	fd = open(filename, O_RDONLY);
	if (!fd)
		return (0);
	src_str = (char*)malloc(max_src_size);
	src_size = read(fd, src_str, max_src_size);
	close(fd);
	p->program = clCreateProgramWithSource(p->context, 1,
		(const char **)&src_str, (const size_t *)&src_size, &ret);
	if (ret < 0)
		return (ocl_error(ret, __func__));
	ret = clBuildProgram(p->program, 1, &(p->device_id), NULL, NULL, NULL);
	if (ret < 0)
		return (ocl_error(ret, __func__));
	free(src_str);
	return (1);
}
