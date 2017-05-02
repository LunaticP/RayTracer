#include "parser.h"

void			rt_add_mask(int *mask_check, int index)
{
	int				check;

	check = 1 << index;
	if (*mask_check & check)
		exit_error("EXIT : s_add_mask [folder_mask.c]");
	*mask_check += check;
}

void				rt_check_all_data(int mask, int check)
{
	printf("\nTEST\n%d\n %d\n", mask, check);
	if (check == 0 || check != mask)
		exit_error("EXIT : s_check_all_data [folder_mask.c]");
}