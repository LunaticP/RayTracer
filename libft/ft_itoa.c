/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:07:44 by pgourran          #+#    #+#             */
/*   Updated: 2015/12/17 20:12:08 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_charint(int n)
{
	int i;

	i = 0;
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	void	ft_intstr(int n, char *str, int len)
{
	str[len] = ((n % 10) + '0');
	if (n > 9)
		ft_intstr(n / 10, str, --len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
	{
		if ((str = (char *)ft_memalloc(12)))
			ft_strcpy(str, "-2147483648");
		return (str);
	}
	len = ft_charint(n) + 1;
	if (!(str = (char *)ft_memalloc(len)))
		return (NULL);
	len -= 2;
	if (str)
	{
		if (n < 0)
		{
			str[0] = '-';
			n = -n;
			ft_intstr(n, str, len);
		}
		else
			ft_intstr(n, str, len);
	}
	return (str);
}
