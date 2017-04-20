/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_finish.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:58:30 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/04 05:03:38 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_finish(t_ocl_prog p)
{
	cl_int	ret;

	if ((ret = clFlush(p.command_queue)) < 0)
		return (ocl_error(ret, __func__));
	if ((ret = clFinish(p.command_queue)) < 0)
		return (ocl_error(ret, __func__));
	if (!(ocl_free_kernel(p)))
		return (0);
	if ((ret = clReleaseProgram(p.program)) < 0)
		return (ocl_error(ret, __func__));
	if ((ret = clReleaseCommandQueue(p.command_queue)) < 0)
		return (ocl_error(ret, __func__));
	if ((ret = clReleaseContext(p.context)) < 0)
		return (ocl_error(ret, __func__));
	return (1);
}
