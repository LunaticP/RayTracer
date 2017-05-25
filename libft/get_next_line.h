/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   langton.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <jogarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 13:13:41 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/25 03:34:26 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"

int	get_next_line(int const fd, char **line);

#endif
