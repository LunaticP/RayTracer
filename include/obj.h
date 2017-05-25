/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 23:43:42 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/23 23:43:43 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include <OpenCL/opencl.h>

typedef enum	e_type
{
	plan,
	sphere,
	cylindre,
	cone,
	light,
	end
}				t_type;

typedef struct	s_obj
{
	cl_float4	pos;
	cl_float4	dir;
	cl_float4	min;
	cl_float4	max;
	cl_float4	mod_tex;
	cl_float4	mod_normal;
	cl_float4	mod_ref;
	cl_float4	mod_trans;
	cl_float	diff;
	cl_float	refl;
	cl_float	trans;
	cl_float	r;
	cl_float	alpha;
	cl_int		col;
	short		tex;
	short		n_m;
	short		r_m;
	short		t_m;
	t_type		type;
}				t_obj;

#endif
