/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_kernel_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:36:33 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/21 20:36:38 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

t_ocl_kernel		ocl_kernel_init(void)
{
	t_ocl_kernel	ret;

	ret.memobj = NULL;
	ret.work_dim = 1;
	ret.obj_size = NULL;
	ret.write = NULL;
	ret.read = NULL;
	ret.kernel = NULL;
	return (ret);
}
