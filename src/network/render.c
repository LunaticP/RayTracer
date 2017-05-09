/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:00:07 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/09 15:27:44 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_network.h>
#include <rt.h>

int	server_render(void)
{
	t_server *serv;

	serv = server(0, NULL);
	if (serv == NULL)
		return (-1);
	serv->render = !serv->render;
	if (serv->render == 1)
		init_render(s);
	return (serv->render);
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

//TODO: change size cut part

int	init_render(t_server *s)
{
	int i;

	i = 0;
	clear_todo(s->todo);
	while (i < HEIGHT)
	{

	}
}
