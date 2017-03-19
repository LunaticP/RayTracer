/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_new_kernel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:56:37 by jplevy            #+#    #+#             */
/*   Updated: 2017/03/04 04:40:26 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_new_kernel(t_ocl_prog *prog, size_t nb_obj, size_t *pws,
		const char *format, ...)
{
	t_ocl_kernel	new;
	va_list			ap;

	new = ocl_kernel_init();
	new.public_work_size = pws;
	new.nb_obj = nb_obj;
	if (!(new.memobj = ft_memalloc(sizeof(cl_mem) * nb_obj)))
		return (0);
	if (!(new.obj_size = ft_memalloc(sizeof(size_t) * nb_obj)))
		return (0);
	if (!(new.write = ft_memalloc(sizeof(void *) * nb_obj)))
		return (0);
	if (!(new.read = ft_memalloc(sizeof(void *) * nb_obj)))
		return (0);
	va_start(ap, format);
	if (!(ocl_get_karg(ap, format, &new, prog)))
		return (0);
	va_end(ap);
	ft_lstpushback(&(prog->kernel), &new, sizeof(t_ocl_kernel));
	return (1);
}
