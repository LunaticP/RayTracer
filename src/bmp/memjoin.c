/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:22:48 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/08 21:01:20 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

void	*memjoin(unsigned char *dst, unsigned char *src, int sdst, int ssrc)
{
	void *mem;

	mem = ft_memalloc(sizeof(unsigned char) * (ssrc + sdst));
	ft_memcpy(mem, dst, sdst);
	ft_memcpy(&mem[sdst], src, ssrc);
	ft_strdel((char **)&dst);
	return (mem);
}
