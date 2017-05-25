/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_set_memobj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:38:41 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:39:09 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_set_memobj(va_list ap, t_ocl_kernel *k, t_ocl_prog *p, int j)
{
	cl_int			ret;

	k->obj_size[j] = (size_t)(va_arg(ap, int));
	k->memobj[j] = clCreateBuffer(p->context, CL_MEM_READ_WRITE,
		k->obj_size[j], NULL, &ret);
	if (ret < 0)
		return (ocl_error(ret, __func__));
	if ((ret = clSetKernelArg(k->kernel, (size_t)j, sizeof(cl_mem),
		(void *)&(k->memobj[j]))) < 0)
		return (ocl_error(ret, __func__));
	k->write[j] = NULL;
	k->read[j] = NULL;
	return (1);
}
