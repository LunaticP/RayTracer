/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 01:22:29 by pgourran          #+#    #+#             */
/*   Updated: 2016/10/13 09:09:50 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl	*ngnl(t_gnl *list, int fd, int next)
{
	t_gnl *new;

	if (!(new = malloc(sizeof(t_gnl))))
		return (NULL);
	if (fd)
		new->ref = fd;
	new->next = NULL;
	new->str = NULL;
	if (next)
		list->next = new;
	return (new);
}

t_gnl	*find_fd(t_gnl *list, int fd)
{
	t_gnl	*ret;

	ret = list;
	while (ret->ref != fd && ret->next)
		ret = ret->next;
	if (ret->ref != fd)
		return (ngnl(ret, fd, 1));
	return (ret);
}

int		get_next_buf(int const fd, int ret, char **save)
{
	char *buf;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(*save = ft_strjoin_free(*save, buf, 1)))
			return (-1);
	}
	if (buf)
		free(buf);
	return (ret);
}

int		ft_endofbuff(char **line, char **s)
{
	if ((*s)[0])
	{
		if (!(*line = ft_strdup(*s)))
			return (-1);
		if (*s)
			free(*s);
		*s = NULL;
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static t_gnl	*s;
	t_gnl			*t;
	int				ret;
	char			*tmp;
	int				tmplen;

	if (!s && fd >= 0 && line)
		s = ngnl(s, fd, 0);
	if (fd < 0 || line == NULL || (!(t = find_fd(s, fd)))
			|| (!(t->str) && (!(t->str = ft_strnew(BUFF_SIZE)))))
		return (-1);
	ret = 1;
	while ((t->str) && (!(tmp = ft_strchr(t->str, '\n')) && ret > 0))
		if ((ret = get_next_buf(fd, ret, &t->str)) == -1)
			return (-1);
	if (ret == 0 || !tmp)
		return (ft_endofbuff(line, &(t->str)));
	if (!(*line = ft_strsub(t->str, 0, tmp - t->str)))
		return (-1);
	tmplen = ft_strlen(tmp + 1);
	if (!(t->str = ft_strsub_free(t->str, tmp - t->str + 1, tmplen)))
		return (-1);
	return (1);
}
