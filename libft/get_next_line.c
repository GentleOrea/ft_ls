/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 11:48:02 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/17 12:58:22 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		chachr(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char		*initline(t_gnl *gl, int fd)
{
	int		i;
	size_t	i2;
	size_t	len;
	char	*temp;

	i = chachr(gl[fd].buf);
	if (!(temp = ft_strnew(i)))
		return (NULL);
	ft_strncat(temp, gl[fd].buf, i);
	i2 = -1;
	len = ft_strlen(&gl[fd].buf[i]);
	while (++i2 < len)
		gl[fd].buf[i2] = gl[fd].buf[(i + 1) + i2];
	gl[fd].buf[i2] = '\0';
	gl[fd].buf = ft_realloc(gl[fd].buf, i2);
	return (temp);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*gl;
	int				ret;
	int				i;
	char			*buf;

	if (BUFF_SIZE < 1 || !line || fd < 0 || fd > 300 || (i = 0) ||
		!(buf = ft_strnew(BUFF_SIZE)) ||
		(!gl && !(gl = (t_gnl*)ft_memalloc(300 * sizeof(t_gnl)))) ||
		(!gl[fd].buf && !(gl[fd].buf = ft_strnew(BUFF_SIZE))))
		return (-1);
	while (!i && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		gl[fd].buf = ft_realloc(gl[fd].buf, (ft_strlen(gl[fd].buf) + ret + 1));
		ft_strncat(gl[fd].buf, buf, ret);
		i = chachr(buf) < ret;
	}
	ft_memdel((void**)&buf);
	if (ret < 0)
		return (-1);
	if (!gl[fd].buf[0])
		return (0);
	return ((*line = initline(gl, fd)) ? 1 : -1);
}
