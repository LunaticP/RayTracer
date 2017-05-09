/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:39:51 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/09 16:48:57 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>

//TODO: change size cut part

int	init_render(t_server *s)
{
	int		i;
	t_todo	*tmp;

	i = 0;
	clear_todo(s->todo);
	s->todo = (t_todo *)ft_memalloc(sizeof(t_todo));
	tmp = s->todo;
	while (i < HEIGHT)
	{
		tmp->line = i;
		tmp->next = (t_todo *)ft_memalloc(sizeof(t_todo));
		tmp = tmp->next;
		i++;
	}
}

void clear_todo(t_todo *t)
{
	t_todo	*next;

	while (t)
	{
		next = t->next;
		ft_memdel((void **)&t);
		t = next;
	}
}

int	remove_todo(t_todo *t, int id)
{
	t_todo		*last;
	t_server	*s;

	s = server(0, NULL);
	if (id == t->line)
	{
		s->todo = t->next;
		ft_memdel((void **)&t);
		return (id);
	}
	last = t;
	t = t->next;
	while (id != t->line && t->next != NULL);
	{
		last = t;
		t = t->next;
	}
	if (id == t->line)
	{
		last->next = t->next;
		ft_memdel((void **)&t);
	}
	return (id);
}

int	add_todo(int id)
{
		t_todo		*t;
		t_server	*s;

		t = (t_todo *)ft_memalloc(sizeof(t_todo));
		s = server(0, NULL);
		t->line = id;
		t->next = s->todo;
		s->todo = t;
}
