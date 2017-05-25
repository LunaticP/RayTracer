/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_enqueue_kernel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:33:26 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:33:30 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int				ocl_enqueue_kernel(t_ocl_prog *prog, char *kernel)
{
	t_ocl_kernel	*k;
	int				i;
	cl_int			ret;

	if (!(k = ocl_get_right_kernel(prog->kernel, kernel)))
		return (0);
	i = -1;
	while (++i < (int)(k->nb_obj))
		if (k->write[i])
			if ((ret = clEnqueueWriteBuffer(prog->command_queue, k->memobj[i],
			CL_TRUE, 0, k->obj_size[i], k->write[i], 0, NULL, NULL)) < 0)
				return (ocl_error(ret, __func__));
	if ((ret = clEnqueueNDRangeKernel(prog->command_queue, k->kernel,
		k->work_dim, NULL, k->public_work_size, 0, 0, NULL, NULL)) < 0)
		return (ocl_error(ret, __func__));
	i = -1;
	while (++i < (int)(k->nb_obj))
		if (k->read[i])
			if ((ret = clEnqueueReadBuffer(prog->command_queue, k->memobj[i],
			CL_TRUE, 0, (k->obj_size)[i], k->read[i], 0, NULL, NULL)) < 0)
				return (ocl_error(ret, __func__));
	return (1);
}
