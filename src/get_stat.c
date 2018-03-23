/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 09:48:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/23 14:47:03 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*path_is_valid(t_global *g, char *path, char *name, int op)
{
	struct stat	st;
	t_ls		*tmp;

	if (!g->b && (!(op & 4) && g->dir->d_name[0] == '.'))
		return (NULL);
	name ? path = ft_strjoin(path, name) : 0;
	if (-1 == lstat(path, &st))
	{
		ls_error(path);
		ft_memdel((void**)&path);
		return (NULL);
	}
	mallcheck(tmp = (t_ls*)ft_memalloc(sizeof(t_ls)));
	tmp->stat = st;
	tmp->path = path;
	get_stat(g, tmp, op);
	return (tmp);
}

void	get_id(t_global *g, t_ls *list, int op)
{
	if (getpwuid(list->stat.st_uid))
		list->uid = ft_strdup(getpwuid(list->stat.st_uid)->pw_name);
	if (getgrgid(list->stat.st_gid))
		list->gid = ft_strdup(getgrgid(list->stat.st_gid)->gr_name);
	g->u_len = ft_ismax(g->u_len, 1 + ((op & 0x400) ?
				ft_row_div(list->stat.st_uid, 10) : ft_strlen(list->uid)));
	g->g_len = ft_ismax(g->g_len, 1 + ((op & 0x400) ?
				ft_row_div(list->stat.st_uid, 10) : ft_strlen(list->gid)));
}

void	get_stat(t_global *g, t_ls *list, int op)
{
	if (!g->b)
	{
		list->type = g->dir->d_type;
		list->name = ft_strdup(g->dir->d_name);
	}
	if (!(op & 1))
		return ;
	g->l_len = ft_ismax(g->l_len, ft_row_div(list->stat.st_nlink, 10));
	if (list->type != DT_CHR)
		g->s_len = ft_ismax(g->s_len, ft_row_div(list->stat.st_size, 10));
	else
	{
		list->min = minor(list->stat.st_rdev);
		list->maj = major(list->stat.st_rdev);
		g->min_len = ft_ismax(g->min_len, 1 + ft_row_div(list->min, 10));
		g->maj_len = ft_ismax(g->maj_len, 1 + ft_row_div(list->maj, 10));
	}
	get_id(g, list, op);
	g->nb_block += list->stat.st_blocks;
}

void	print_id(t_global *g, t_ls *list, int op)
{
	(op & 0x400) ? ft_printf("%-*d %-*d", g->u_len,
			list->stat.st_uid, g->g_len, list->stat.st_gid) : 0;
	!(op & 0x2400) && list->uid ? ft_printf("%-*s ", g->u_len, list->uid) : 0;
	!(op & 0x440) && list->gid ? ft_printf("%-*s ", g->g_len, list->gid) : 0;
	(op & 0x2000 && op & 0x40) ? ft_printf("  ") : 0;
}

void	print_stat(t_global *g, t_ls *list, int op)
{
	char	**tab;
	time_t	tme2;
	int		tme;

	tme2 = list->stat.st_mtime;
	(op & 0x100) ? tme2 = list->stat.st_ctime : 0;
	(op & 0x200) ? tme2 = list->stat.st_atime : 0;
	(op & 0x800) ? tme2 = list->stat.st_birthtime : 0;
	if ((tme = time(NULL) - tme2) > 15778800 || tme < 0)
		tme = 1;
	else
		tme = 0;
	convert_mode(list->stat.st_mode, list);
	ft_printf("%*u ", g->l_len, (unsigned long)list->stat.st_nlink);
	print_id(g, list, op);
	list->type != DT_CHR ? ft_printf("%*u ", g->s_len, list->stat.st_size)
		: ft_printf("%*d, %*d ", g->maj_len, list->maj, g->min_len, list->min);
	tab = ft_strsplit(ctime(&tme2), ' ');
	ft_printf("%s %2s %*.*s ", tab[1], tab[2], !tme ? 0 : 5, !tme ? 5 :
			ft_strlen(tab[4]) - 1, !tme ? tab[3] : tab[4]);
	ft_free_dblechar_tab(tab);
}
