/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_get_karg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:35:40 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:35:43 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

int		ocl_get_karg(va_list ap, const char *str, t_ocl_kernel *k,
		t_ocl_prog *p)
{
	int				i;
	int				j;
	cl_int			ret;

	i = -1;
	j = -1;
	k->name = NULL;
	while (str[++i])
	{
		if (str[i] == 'D' || str[i] == 'd')
			k->work_dim = (size_t)va_arg(ap, int);
		if ((str[i] == 'O' || str[i] == 'o') && ++j < (int)(k->nb_obj))
			if (!(ocl_set_memobj(ap, k, p, j)))
				return (0);
		if ((str[i] == 'W' || str[i] == 'w') && j < (int)(k->nb_obj) && j >= 0)
			k->write[j] = va_arg(ap, void *);
		if ((str[i] == 'R' || str[i] == 'r') && j < (int)(k->nb_obj) && j >= 0)
			k->read[j] = va_arg(ap, void *);
		if (str[i] == 'N' || str[i] == 'n')
			if ((k->name = va_arg(ap, char *)) &&
				(k->kernel = clCreateKernel(p->program, k->name, &ret)) &&
				ret < 0)
				return (ocl_error(ret, __func__));
	}
	return (1);
}
