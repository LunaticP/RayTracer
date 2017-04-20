/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <aviau@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 04:22:38 by aviau             #+#    #+#             */
/*   Updated: 2017/04/06 05:51:49 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
}

int		get_next_line(int const fd, char **line)
{
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
}
