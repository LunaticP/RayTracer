/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:22:48 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 15:59:24 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

void	*memjoin(char *dst, char *src, int sdst, int ssrc)
{
	void *mem;

	mem = ft_memalloc(sizeof(char) * (ssrc + sdst));
	ft_memcpy(mem, dst, sdst);
	ft_memcpy(&mem[sdst], src, ssrc);
	ft_strdel(&dst);
	return (mem);
}
