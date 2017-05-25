/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:22:48 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/25 03:38:00 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_bmp.h>
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
