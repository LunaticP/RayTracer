/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_get_right_kernel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:36:07 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:36:08 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

t_ocl_kernel	*ocl_get_right_kernel(t_list *start, char *kernel)
{
	t_list			*tmp;

	tmp = start;
	while (tmp)
	{
		if (ft_strcmp(((t_ocl_kernel *)(tmp->content))->name, kernel) == 0)
			return ((t_ocl_kernel *)tmp->content);
		tmp = tmp->next;
	}
	ft_putendl("wrong kernel enqueued");
	return (NULL);
}
