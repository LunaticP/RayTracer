/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:39:51 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/10 20:44:21 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <libft.h>
#define SCALE 20

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
		i += SCALE;
	}
	return (0);
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

int	remove_todo(void)
{
	t_todo		*td;
	t_server	*s;

	s = server(0, NULL);
	td = s->todo->next;
	ft_memdel((void **)&(s->todo));
	s->todo = td;
	return (0);
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
	return (0);
}

void	get_newtodo(t_client *c)
{
	t_server	*s;

	s = server(0, NULL);
	c->line = s->todo->line;
	remove_todo();
}












































/* ************************************************************************** */
