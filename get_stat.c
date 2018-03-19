/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 09:48:05 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/19 18:36:25 by ygarrot          ###   ########.fr       */
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

void	convert_mode(mode_t st_mode)
{
	char	s[11];
	int		i;

	i = -1;
	while (++i < 3)
	{
		s[10 - 3 - (i * 3)] = (st_mode & (4 << (i * 3))) ? 'r' : '-';
		s[10 - 2 - (i * 3)] = (st_mode & (2 << (i * 3))) ? 'w' : '-';
		s[10 - 1 - (i * 3)] = (st_mode & (1 << (i * 3))) ? 'x' : '-';
	}
	s[0] = if_forest(st_mode);
	s[10] = 0;
	ft_printf("%s  ", s);
}

void	get_stat(t_global *g, t_ls *list, char *argv)
{
	//	ft_printf("%s\n", argv);
	if (stat(argv, &list->stat) == -1) 
	{
		perror("stat");
		return ;
	}
	g->l_len = ft_ismax(g->l_len, 1 + ft_row_div(list->stat.st_nlink, 10));
	g->s_len = ft_ismax(g->s_len, 1 + ft_row_div(list->stat.st_size, 10));
	list->uid = getpwuid(list->stat.st_uid)->pw_name;
	list->gid = getgrgid(list->stat.st_gid)->gr_name;
	g->u_len = ft_ismax(g->u_len, ft_strlen(list->uid));
	g->g_len = ft_ismax(g->g_len, ft_strlen(list->gid));
	g->nb_block += list->stat.st_blocks;
	if (list->name)
		return ;
	list->type = g->dir->d_type;
	list->name = ft_strdup(g->dir->d_name);
}


void	print_stat(t_global *g, t_ls *list)
{
	char	**tab;
	char	link[256];
	
	ft_bzero(link, sizeof(link));
	int i;
	(i = readlink(list->path, link, 256)) > 0 ? lstat(link, &list->stat) : 0;
	convert_mode(list->stat.st_mode);
	ft_printf("%*u ", g->l_len, (unsigned long)list->stat.st_nlink);
	//printf("Propriétaires :                    UID=%ld   GID=%ld\n",
	//		(long) list->stat.st_uid, (long) list->stat.st_gid);
	ft_printf("%-*s %-*s ", g->u_len, list->uid, g->g_len,list->gid);
	ft_printf(" %*u ", g->s_len, (unsigned long)list->stat.st_size);
	//printf("Dernier changement d’état :        %s", ctime(&list->stat.st_ctime));
	//printf("Dernier accès au fichier :         %s", ctime(&list->stat.st_atime));
	tab = ft_strsplit(ctime(&list->stat.st_mtime), ' ');
	ft_printf("%s %2s %.5s ", tab[1], tab[2], tab[3]);
	ft_free_dblechar_tab(tab);
}
