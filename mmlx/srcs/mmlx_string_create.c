/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_string_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 03:46:35 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/19 18:25:51 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

static int	mmlx_check_data(t_mmlx *win, t_stringput *data)
{
	if (!(data->xpos >= 0 && data->xpos < win->xwin))
		return (mmlx_error(__func__, WRONG_XSTART_STRING));
	else if (!(data->ypos >= 0 && data->xpos < win->ywin))
		return (mmlx_error(__func__, WRONG_YSTART_STRING));
	else if (!(data->f_string || data->string))
		return (mmlx_error(__func__, LACK_OF_DATA_FOR_STRING));
	else if (data->f_string && data->string)
		return (mmlx_error(__func__, TOO_MANY_DATA_FOR_STRING));
	return (0);
}

static int	mmlx_string_freespace(int *i, int *string_used)
{
	while (*i < DFLT_MAX_STRINGWIN && string_used[*i])
		(*i)++;
	if (*i >= DFLT_MAX_STRINGWIN)
		return (mmlx_error(__func__, MAX_STRINGWIN_ERROR));
	return (0);
}

int			mmlx_string_create(t_mmlx *win, t_stringput *data)
{
	int			i;

	i = 0;
	if (mmlx_error(__func__, mmlx_string_freespace(&i, win->string_used)))
		return (-1);
	if (mmlx_error(__func__, mmlx_check_data(win, data)))
		return (-1);
	win->string_tab[i].color = data->color;
	win->string_tab[i].ypos = data->ypos;
	win->string_tab[i].xpos = data->xpos;
	win->string_tab[i].f_data = data->f_data;
	if (data->string)
		win->string_tab[i].string = ml_strdup(data->string);
	else
		win->string_tab[i].string = NULL;
	win->string_tab[i].f_string = data->f_string;
	win->string_used[i] = 1;
	return (i);
}
