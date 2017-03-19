/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_kernel_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:55:54 by jplevy            #+#    #+#             */
/*   Updated: 2017/02/22 19:04:26 by jplevy           ###   ########.fr       */
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
