/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 21:34:13 by jogarcia          #+#    #+#             */
/*   Updated: 2015/12/03 18:11:37 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *ptr;

	if (lst && f)
	{
		new = f(lst);
		ptr = new;
	}
	while (lst->next)
	{
		new->next = f(lst->next);
		lst = lst->next;
		new = new->next;
	}
	if (ptr)
		return (ptr);
	return (NULL);
}
