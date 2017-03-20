/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseobj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 08:15:32 by pgourran          #+#    #+#             */
/*   Updated: 2017/03/20 10:58:07 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		obj_error(void)
{
	ft_putendl("obj_error !");
	exit(0);
}

//Implementer lsttotab & freelst

cl_float	ft_get_value(char *str)
{
	cl_float	res;
	int			pos;
	char		neg;

	pos = 0;
	res = ft_atoi(str);
	if(str[0] == '-')
		neg = 1;
	else
		neg = 0;
	while(str[pos] != '.')
		pos++;
	pos++;
	if(neg)
		res -= (cl_float)ft_atoi(&str[pos]) / 1000000;
	else
		res += (cl_float)ft_atoi(&str[pos]) / 1000000;
	return(res);
}



t_list		*get_obj(char *path)
{
	t_list		*file;
	char		**data;
	t_list		*obj;
//	t_triangle	tri;
	int			y;
	int			x;
	file = get_file(path);
	data = ft_lsttotab(file);
	t_list		*pts;
	cl_float4	p;
	cl_float4	*l;
//	ft_freelst(&file);
	y = 0;
	ft_puttab(data);
	obj = NULL;
	pts = NULL;
	while(data[y][0] != 'v' || data[y][1] != ' ')
		y++;
	data += y;
	y = 0;
	ft_putstr("Vertex Loading : ");
	ft_putstr("\033[32;7m\n");
	while(data[y][0] == 'v' && data[y][1] == ' ')
	{
		x = 2;
//		ft_putchar(' ');
		p.x = ft_get_value(&data[y][x]);
		while(data[y][x] != ' ')
			x++;
		x++;
		p.y = ft_get_value(&data[y][x]);
		while(data[y][x] != ' ')
			x++;
		x++;
		p.z = ft_get_value(&data[y][x]);
		ft_lstpushback(&pts, &p, sizeof(p));
		y++;
	}
	while(pts->next)
	{
		l = pts->content;
		printf("%f : %f : %f\n",l->x,l->y,l->z);
		pts = pts->next;
		
	}
	ft_putstr("\033[32;0m ");
	ft_putnbr(y);
	ft_putstr(" vertex loaded !");
//	ft_lstpushback(&pts, , sizeof(t_triangle));
	return(obj);
//	while(data)
}
