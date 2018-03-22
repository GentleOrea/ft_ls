/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:41:28 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/22 15:42:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	if_forest(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else if ((st_mode & S_IFMT) == S_IFREG)
		return ('-');
	return ('-');
}

char	special_bit(mode_t st_mode, int decal, int row)
{
	if (row == 0 && (st_mode & S_ISVTX))
		return (st_mode & decal ? 't' : 'T');
	else if (row == 1 && st_mode & S_ISGID)
		return (st_mode & decal ? 's' : 'S');
	else if (row == 2 && st_mode & S_ISUID)
		return (st_mode & decal ? 's' : 'S');
	return ('\0');
}

void	convert_mode(mode_t st_mode, t_ls *list)
{
	char	s[12];
	char attr[256];
	int		i;
	char	ac;

	i = -1;
	ft_bzero(attr, sizeof(attr));
	while (++i < 3)
	{
		s[10 - 3 - (i * 3)] = (st_mode & (4 << (i * 3))) ? 'r' : '-';
		s[10 - 2 - (i * 3)] = (st_mode & (2 << (i * 3))) ? 'w' : '-';
		if ((ac = special_bit(st_mode, st_mode & (1 << (i * 3)), i)))
			s[10 - 1 - (i * 3)] = ac;
		else
			s[10 - 1 - (i * 3)] = (st_mode & (1 << (i * 3))) ? 'x' : '-';
	}
	s[0] = if_forest(st_mode);
	ac = acl_get_link_np(list->path, ACL_TYPE_EXTENDED) ? '+' : ' ';
	ac = (listxattr(list->path, attr, 255, XATTR_NOFOLLOW | XATTR_SHOWCOMPRESSION) > 0 ? '@' : ac);
	s[10] = ac;
	s[11] = '\0';
	ft_printf("%s ", s);
}


