#include "parser.h"

static int		s_check_01(cl_float var_test);

void		rt_check_value(void ***tab)
{
	t_obj *ptr;

	ptr = (t_obj *)tab[0];
	while (ptr->type != end)
	{
		if (s_check_01(ptr->diff) || s_check_01(ptr->refr)
				|| s_check_01(ptr->refr) || s_check_01(ptr->trans))
			exit_error("EXIT : [rt_check_value.c] 1");
		if (!(0 <= ptr->alpha && ptr->alpha <= 180) || !(0 <= ptr->caps && ptr->caps <= 3))
			exit_error("EXIT : [rt_check_value.c] 2");
		++ptr;
	}
}

static int		s_check_01(cl_float var_test)
{
	if (0 <= var_test && var_test <= 1)
		return (0);
	return (-1);
}
