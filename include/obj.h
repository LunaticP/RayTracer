/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 20:21:23 by aviau             #+#    #+#             */
/*   Updated: 2017/05/22 12:41:34 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <OpenCL/opencl.h>

typedef enum		e_type
{
	plan,
	sphere,
	cylindre,
	cone,
	para,
	light,
	end
}					t_type;

typedef struct		s_obj
{
	cl_float4		pos;
	cl_float4		dir;
	cl_float4		min;
	cl_float4		max;
	cl_int			col;
	cl_float		diff;
	cl_float		refl;
	cl_float		trans;
	t_type			type;
	cl_float		r;
	cl_float		alpha;
	cl_float4		mod_tex;
	cl_float4		mod_normal;
	cl_float4		mod_ref;
	cl_float4		mod_trans;
	short			tex;
	short			n_m;
	short			r_m;
	short			t_m;
}					t_obj;

#endif
