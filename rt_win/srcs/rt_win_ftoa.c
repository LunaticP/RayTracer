/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_win_ftoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 05:46:32 by gsimeon           #+#    #+#             */
/*   Updated: 2017/05/04 10:28:55 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_win.h"

char	*rt_win_ftoa(float number)
{
	char	*int_part;
	char	*flt_part;
	char	*num;
	char	*tmp;
	char	*sign;

	sign = (number < 0 ? "-" : "+");
	int_part = ft_itoa((int)fabs(number));
	flt_part = ft_itoa((int)(
						fabs(number - (int)number) * pow(10, FTOA_NUM_FLOAT)));
	num = ft_strnew(ft_strlen(int_part) + FTOA_NUM_FLOAT + 2);
	tmp = num;
	ft_memcpy(tmp, sign, 1);
	tmp += 1;
	ft_memcpy(tmp, int_part, ft_strlen(int_part));
	tmp += ft_strlen(int_part);
	ft_memcpy(tmp, FTOA_SEPARATOR, 1);
	tmp += 1;
	ft_memset(tmp, '0', FTOA_NUM_FLOAT);
	tmp += FTOA_NUM_FLOAT - ft_strlen(flt_part);
	ft_memcpy(tmp, flt_part, ft_strlen(flt_part));
	ft_strdel(&int_part);
	ft_strdel(&flt_part);
	return (num);
}
