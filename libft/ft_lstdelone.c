/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 18:20:26 by jogarcia          #+#    #+#             */
/*   Updated: 2015/12/03 18:15:17 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	if (*alst)
	{
		ptr = *alst;
		del(ptr->content, ptr->content_size);
		free(*alst);
		*alst = NULL;
	}
}
