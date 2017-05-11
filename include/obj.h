/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 20:21:23 by aviau             #+#    #+#             */
/*   Updated: 2017/05/11 13:04:24 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <OpenCL/opencl.h>

typedef enum		e_type
{
	plan,
	triangle,
	sphere,
	cylindre,
	cone,
	para,
	light,
	end
}					t_type;

typedef struct 		s_obj
{
	cl_float4		pos;
	cl_float4		dir;
	float			tet;
	float			phi;
	float			rot;
	cl_float4		min;
	cl_float4		max;
	cl_int			col;
	cl_float		diff;
	cl_float		refl;
	cl_float		trans;
	cl_float		refr;
	t_type			type;
	cl_float		r;
	cl_float		su;
	cl_float		sd;
	cl_float		alpha;
	cl_char			caps;
	cl_float4		p1;
	cl_float4		p2;
	cl_float4		p3;
	short			tex;
	short			n_m;
	short			r_m;
	short			t_m;
}					t_obj;

#endif
