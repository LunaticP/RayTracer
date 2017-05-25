/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 21:03:47 by jogarcia          #+#    #+#             */
/*   Updated: 2015/12/03 18:12:10 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;

	if (*alst && del)
	{
		ptr = *alst;
		while (ptr->next)
		{
			del(ptr->content, ptr->content_size);
			ptr = ptr->next;
			free(*alst);
			*alst = ptr;
		}
		del(ptr->content, ptr->content_size);
		free(*alst);
		*alst = NULL;
	}
}
