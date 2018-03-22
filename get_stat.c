/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 09:48:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/22 15:42:24 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*path_is_valid(t_global *g, char *path, char *name, int op)
{
	struct stat st;
	t_ls	*tmp;

	if (name)
		path = ft_strjoin(path, name);
	(void)g;
	if (!g->b && (!(op & 4) && g->dir->d_name[0] == '.'))
		return (NULL);
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
void		get_stat(t_global *g, t_ls *list, int op)
{
	//if (list->name && !g->b)
	//	return ;
	if (!g->b)
	{
		list->type = g->dir->d_type;
		list->name = ft_strdup(g->dir->d_name);
	}
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
	list->uid = getpwuid(list->stat.st_uid)->pw_name;
	list->gid = getgrgid(list->stat.st_gid)->gr_name;
	g->u_len = ft_ismax(g->u_len, 1 + ((op & 32768) ? ft_row_div(list->stat.st_uid, 10) : ft_strlen(list->uid)));
	g->g_len = ft_ismax(g->g_len, 1 + ((op & 32768) ? ft_row_div(list->stat.st_uid, 10) : ft_strlen(list->gid)));
	g->nb_block += list->stat.st_blocks;
}


void	print_stat(t_global *g, t_ls *list, int op)
{
	char	**tab;
	int		tme;

	tab = NULL;
	if ((tme = time(NULL) - list->stat.st_mtime) > 15778800  || tme < 0)
	{
		//ft_printf("{red}%d{reset}\n", tme);
		tme = 1;
	}
	else
		tme = 0;
	//ft_printf("{red}%d, %d{reset}\n", g->s_len, g->g_len);
	convert_mode(list->stat.st_mode, list);
	ft_printf("%*u ", g->l_len, (unsigned long)list->stat.st_nlink);
	op & 32768 ? ft_printf("%-*d %-*d", g->u_len, list->stat.st_uid, g->g_len, list->stat.st_gid) :
	ft_printf("%-*s %-*s ", g->u_len, list->uid, g->g_len, list->gid);
	list->type != DT_CHR ? ft_printf("%*u ", g->s_len, (unsigned long)list->stat.st_size)
		: ft_printf("%*d, %*d ", g->maj_len,list->maj,g->min_len, list->min);
	//printf("Dernier changement d’état :        %s", ctime(&list->stat.st_ctime));
	//printf("Dernier accès au fichier :         %s", ctime(&list->stat.st_atime));
	(op & 0x40) ? tab = ft_strsplit(ctime(&list->stat.st_ctime), ' ') : 0;
	(op & 0x800) ? tab = ft_strsplit(ctime(&list->stat.st_atime), ' ') : 0;
	!tab ?tab = ft_strsplit(ctime(&list->stat.st_mtime), ' '): 0;
	//	int i = -1;
//	while (tab[++i])
//		ft_printf("{red}%s{reset}\n", tab[i]);
	ft_printf("%s %2s %*.*s ", tab[1], tab[2], !tme ? 0 : 5, !tme ? 5 : 4, !tme ? tab[3] : tab[4]);
	ft_free_dblechar_tab(tab);
}
