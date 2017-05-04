/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getaddress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:25:28 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/03 11:33:05 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char *getaddress(char *poste)
{
	char	*e_place;
	char	*r_place;
	char	*p_place;
	char	*ret;

	ret = ft_strnew(0);
	e_place = ft_strchr(poste, 'e');
	r_place = ft_strchr(poste, 'r');
	p_place = ft_strchr(poste, 'p');
	ret = ft_freejoin(ret, "10.1");
	ret = ft_freejoin(ret, ft_itoa(ft_atoi((e_place + 1))));
	ret = ft_freejoin(ret, ".");
	ret = ft_freejoin(ret, ft_itoa(ft_atoi((r_place + 1))));
	ret = ft_freejoin(ret, ".");
	ret = ft_freejoin(ret, ft_itoa(ft_atoi((p_place + 1))));
	return (ret);
}
