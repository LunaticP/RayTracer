/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_struct_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:55:29 by jplevy            #+#    #+#             */
/*   Updated: 2017/02/22 19:04:53 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libocl.h"

t_ocl_prog		ocl_struct_init(void)
{
	t_ocl_prog	ret;

	ret.device_id = NULL;
	ret.context = NULL;
	ret.command_queue = NULL;
	ret.program = NULL;
	ret.kernel = NULL;
	ret.platform_id = NULL;
	return (ret);
}
