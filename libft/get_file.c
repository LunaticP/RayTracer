/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:09:28 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/15 16:10:10 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*get_file(char *path)
{
	int		fd;
	t_list	*file;
	t_list	*ptr;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(ptr = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	file = ptr;
	while (0 < get_next_line(fd, &line))
	{
		ptr->content_size = sizeof(line);
		ptr->content = ft_strdup(line);
		if (!(ptr->next = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		ptr = ptr->next;
		free(line);
	}
	ptr->next = NULL;
	ptr->content_size = sizeof(ptr->content);
	return (file);
}
