/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseobj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 08:15:32 by pgourran          #+#    #+#             */
/*   Updated: 2017/03/21 17:07:56 by pgourran         ###   ########.fr       */
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

cl_float4	get_content(t_list *list, int num)
{
	num++;
	t_list *ptr;
	cl_float4	*fl;

	ptr = list;
	while(--num && ptr->next)
		ptr = ptr->next;
	fl = ptr->content;
	return(*fl);
}

t_list		*get_obj(char *path)
{
	t_list		*file;
	char		**data;
	t_list		*obj;
	t_triangle	tri;
	t_triangle	*tro;
	int			y;
	int			x;
	file = get_file(path);
	data = ft_lsttotab(file);
	t_list		*pts;
	t_list		*pns;
	t_list		*tris;
	cl_float4	p;
	cl_float4	pn;
//	ft_freelst(&file);
	y = 0;
	obj = NULL;
	pts = NULL;
	pns = NULL;
	tris = NULL;
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
	while(data[y][0] == 'v' && data[y][1] == 'n')
	{
		x = 3;
		pn.x = ft_get_value(&data[y][x]);
		while(data[y][x] != ' ')
			x++;
		x++;
		pn.y = ft_get_value(&data[y][x]);
		while(data[y][x] != ' ')
			x++;
		x++;
		pn.z = ft_get_value(&data[y][x]);
		ft_lstpushback(&pns, &pn, sizeof(pn));
		y++;
	}
	y++;
	while(data[y] && data[y][0] == 'f' && data[y][1] == ' ')
	{
		x = 2;
		tri.p1 = get_content(pts, ft_atoi(&data[y][x]));
		x += 2;
		while(data[y][x] != '/')
			x++;
		x++;
		tri.vn1 = get_content(pns, ft_atoi(&data[y][x]));
		while(data[y][x] != ' ')
			x++;
		x++;
		tri.p2 = get_content(pts, ft_atoi(&data[y][x]));
		x += 2;
		while(data[y][x] != '/')
			x++;
		x++;
		tri.vn2 = get_content(pns, ft_atoi(&data[y][x]));
		while(data[y][x] != ' ')
			x++;
		x++;
		tri.p3 = get_content(pts, ft_atoi(&data[y][x]));
		x += 2;
		while(data[y][x] != '/')
			x++;
		x++;
		tri.vn3 = get_content(pns, ft_atoi(&data[y][x]));
		while(data[y][x] != ' ')
			x++;
		x++;
		ft_lstpushback(&tris, &tri, sizeof(tri));
		y++;
	}
	while(tris->next)
	{
		tro = tris->content;
//		printf("%f : %f : %f\n",tro->p1.x,tro->p1.y,tro->p1.z);
//		printf("%f : %f : %f\n",tro->p2.x,tro->p2.y,tro->p2.z);
//		printf("%f : %f : %f\n",tro->p3.x,tro->p3.y,tro->p3.z);
//		printf("%f : %f : %f\n",tro->vn1.x,tro->vn1.y,tro->vn1.z);
//		printf("%f : %f : %f\n",tro->vn2.x,tro->vn2.y,tro->vn2.z);
//		printf("%f : %f : %f\n",tro->vn3.x,tro->vn3.y,tro->vn3.z);
		tris = tris->next;
		
	}
	ft_putstr("\033[32;0m ");
	ft_putnbr(y);
	ft_putstr(" vertex loaded !");
//	ft_lstpushback(&pts, , sizeof(t_triangle));
	return(obj);
//	while(data)
}
