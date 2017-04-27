/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: aviau <aviau@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 04:22:38 by aviau             #+#    #+#             */
/*   Updated: 2017/04/06 05:51:49 by aviau            ###   ########.fr       */
=======
/*   By: pgourran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 01:22:29 by pgourran          #+#    #+#             */
/*   Updated: 2016/10/13 09:09:50 by pgourran         ###   ########.fr       */
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD
char	*free_join(char *dst, char *src)
{
	char	*tmp;

	tmp = dst;
	dst = ft_strjoin(dst, src);
	free(tmp);
	return (dst);
}

int		freeturn(char *buf, int r)
{
	free(buf);
	return (r);
}

int		save_buf(int index, char **line)
{
	static char	*save;
	char		*tmp;
	int			i;
	int			ret;

	if (!(i = 0) && index)
	{
		free(save ? save : NULL);
		return (((save = ft_strdup((char *)line + index)) == NULL) ? -1 : 1);
	}
	else if (!save)
		return (0);
	else
	{
		while (save[i] && save[i] != '\n')
			i++;
		ret = (save[i] == '\n') ? 1 : 0;
		save[i] = '\0';
		*line = ft_strjoin(*line, save);
		tmp = (ret) ? ft_strdup(&save[i + 1]) : ft_strdup("");
		free(save);
		save = tmp;
		return (ret);
	}
=======
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
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
}

int		get_next_line(int const fd, char **line)
{
<<<<<<< HEAD
	int		r;
	int		i;
	int		rd;
	char	*buf;

	if ((r = 1) && (fd < 0 || !line))
		return (-1);
	buf = ft_strnew(BUFF_SIZE + 1);
	if ((*line = ft_strnew(0)) && save_buf(0, line))
		return (freeturn(buf, r));
	rd = 1;
	while (!(BUFF_SIZE == 1 && !rd) && (r > 0 && !(i = 0)))
	{
		ft_strclr(buf);
		if ((rd = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		while (r > 0 && buf[i] && buf[i] != '\n')
			i++;
		r = (buf[i] == '\n' || !rd) ? 0 : 1;
		buf[i] = '\0';
		*line = free_join(*line, buf);
		r = (save_buf(i + 1, (char **)buf) == -1) ? -1 : r;
	}
	r = (BUFF_SIZE == 1) ? rd : r;
	return (freeturn(buf, (*line[0] || buf[i + 1]) ? 1 : r));
=======
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
>>>>>>> 87a7f5cd22e3c792d8000f39fac31351443ceff1
}
