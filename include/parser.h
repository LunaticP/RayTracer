#ifndef PARSER_H
# define PARSER_H

#include "rt.h"

typedef struct		s_data
{
	char			*name;
	int				size;
	void			*(*ft_conv)(char *);
}					t_data;

typedef struct		s_type_elem
{
	char			*name;
	t_parser		*(*ft_elem)();
}					t_type_elem;

typedef struct		s_objects
{
	char	*name;
	int		mask;
}
					t_objects;
# endif