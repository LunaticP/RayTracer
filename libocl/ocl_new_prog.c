/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_new_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:56:13 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/04 04:42:26 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_new_prog(char *filename, size_t max_src_size, t_ocl_prog *p)
{
	cl_int		ret;

	*p = ocl_struct_init();
	ret = clGetPlatformIDs(1, &(p->platform_id), &(p->ret_num_platforms));
	if (ret < 0)
		return (ocl_error(ret, __func__));
	ret = clGetDeviceIDs(p->platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
		&(p->device_id), &(p->ret_num_devices));
	if (ret < 0)
		return (ocl_error(ret, __func__));
	if ((p->context = clCreateContext(NULL, 1, &(p->device_id), NULL,
		NULL, &ret)) && ret < 0)
		return (ocl_error(ret, __func__));
	p->command_queue = clCreateCommandQueue(p->context, p->device_id, 0, &ret);
	if (ret < 0)
		return (ocl_error(ret, __func__));
	if (!(ocl_build_prog(filename, max_src_size, p)))
		return (0);
	return (1);
}
