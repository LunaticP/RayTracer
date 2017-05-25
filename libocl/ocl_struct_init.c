/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_struct_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:39:25 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:39:26 by jogarcia         ###   ########.fr       */
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
