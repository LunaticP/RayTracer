/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_build_prog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:33:02 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:33:03 by jogarcia         ###   ########.fr       */
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
