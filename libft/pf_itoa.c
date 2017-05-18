/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 02:51:24 by gsimeon           #+#    #+#             */
/*   Updated: 2016/03/26 23:49:56 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

inline static int		pf_base(char output)
{
	if (output == 'd' || output == 'i' || output == 'u')
		return (10);
	else if (output == 'x' || output == 'p')
		return (16);
	else if (output == 'o')
		return (8);
	else if (output == 'b')
		return (2);
	return (0);
}

inline static __int128	pf_cast_upper(void *ptr, char s, int flags)
{
	__int128		i;

	i = 0;
	if (flags & 64)
	{
		if (s)
			i = (__int128)((ssize_t)ptr);
		else
			i = (__int128)((size_t)ptr);
	}
	else if (flags & 32)
	{
		if (s)
			i = (__int128)((intmax_t)ptr);
		else
			i = (__int128)((uintmax_t)ptr);
	}
	else if (flags & 16)
	{
		if (s)
			i = (__int128)((long long)ptr);
		else
			i = (__int128)((unsigned long long)ptr);
	}
	return (i);
}

inline static __int128	pf_cast(void *ptr, char s, int flags)
{
	__int128		i;

	if (flags & 112)
		i = pf_cast_upper(ptr, s, flags);
	else if (flags & 8)
	{
		if (s)
			i = (__int128)((long)ptr);
		else
			i = (__int128)((unsigned long)ptr);
	}
	else if (flags & 2)
		i = (__int128)(s ? (short)ptr : (unsigned short)ptr);
	else if (flags & 4)
		i = (__int128)(s ? (char)ptr : (unsigned char)ptr);
	else
	{
		if (s)
			i = (__int128)((int)ptr);
		else
			i = (__int128)((unsigned int)ptr);
	}
	return (i);
}

char					*pf_itoa(void *ptr, char output, int flags)
{
	char		tmp[65];
	__int128	n;
	int			i;
	int			base;

	i = 63;
	tmp[64] = '\0';
	ft_memset(tmp, '0', 64);
	n = pf_cast(ptr, 0, flags);
	if ((base = pf_base(output)) == 10 && output != 'u')
		n = pf_cast(ptr, 1, flags);
	while (n)
	{
		if ((tmp[i] = n % base) < 0)
		{
			tmp[i] = -tmp[i];
			tmp[i - 1] = '-';
		}
		tmp[i] += (tmp[i] < 10 ? '0' : ('a' - 10));
		i--;
		n /= base;
	}
	if (tmp[i] == '-' || i == 63)
		i--;
	return (ft_strdup(&(tmp[i + 1])));
}
