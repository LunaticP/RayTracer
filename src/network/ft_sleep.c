/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 11:39:21 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/05 11:39:46 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>

void	ft_sleep(int t)
{
	time_t	timedelay;
	time_t	start;

	time(&start);
	while (1)
	{
		time(&timedelay);
		if ((timedelay - start) >= t)
			return ;
	}
	return ;
}
