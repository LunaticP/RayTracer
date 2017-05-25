/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 08:54:26 by jogarcia          #+#    #+#             */
/*   Updated: 2016/10/17 15:40:17 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *lst)
{
	int		i;
	t_list	*list;

	i = 0;
	if (lst)
	{
		list = lst;
		while (list)
		{
			i++;
			list = list->next;
		}
	}
	return (i);
}
