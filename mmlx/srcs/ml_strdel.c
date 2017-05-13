/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 00:42:22 by gsimeon           #+#    #+#             */
/*   Updated: 2017/04/10 00:53:11 by gsimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmlx.h"

void	ml_strdel(char **as)
{
	free((void*)*as);
	*as = NULL;
}