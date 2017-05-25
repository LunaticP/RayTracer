/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_finish.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:34:12 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:34:13 by jogarcia         ###   ########.fr       */
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
