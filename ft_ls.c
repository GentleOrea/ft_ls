/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:18:39 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/18 15:58:07 by ygarrot          ###   ########.fr       */
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
	return ('\0');
}

void	convert_mode(mode_t		st_mode)
{	
	char	s[11];
	int i;

	i = -1;
	while (++i < 3)
	{
		s[10 - 3 - (i * 3)] = (st_mode & (4 << (i * 3))) ? 'r' : '-';
		s[10 - 2 - (i * 3)] = (st_mode & (2 << (i * 3))) ? 'w' : '-';
		s[10 - 1 - (i * 3)] = (st_mode & (1 << (i * 3))) ? 'x' : '-';
	}
	s[0] = if_forest(st_mode);
	s[10] = 0;
	i = -1;
	ft_printf("%s", s);
}

void	get_stat(char *argv)
{
	struct stat sb;
	struct passwd *tmp;
	struct group *grp;

	if (stat(argv, &sb) == -1) {
		perror("stat");
		return ;
		//exit(EXIT_SUCCESS);
	}
	//printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);
	convert_mode(sb.st_mode);
	ft_printf("%5ld", (long) sb.st_nlink);
	//printf("Propriétaires :                    UID=%ld   GID=%ld\n",
	//		(long) sb.st_uid, (long) sb.st_gid);

	tmp = getpwuid(sb.st_uid);
	grp = getgrgid(sb.st_gid);

	ft_printf("%8s  %8s", tmp->pw_name, grp->gr_name);
	//printf("%5ld ",(long) sb.st_blksize);

	ft_printf("%8lld", (long long) sb.st_size);
	//printf("Blocs alloués :                    %lld\n",
	//		(long long) sb.st_blocks);

	//printf("Dernier changement d’état :        %s", ctime(&sb.st_ctime));
	//printf("Dernier accès au fichier :         %s", ctime(&sb.st_atime));
	char	**tab;
	tab = ft_strsplit(ctime(&sb.st_mtime), ' ');
	ft_printf(" %s %s %s", tab[1], tab[2], tab[3]);
}

void	sort_files(t_ls *begin, char *str, char op)
{
	t_ls	*tmp;
	int		diff;

	tmp = begin;
	while (tmp->next && tmp->next->name)
	{
		diff = ft_strcmp(tmp->name, tmp->next->name);
		if (diff > 0)
		{
			swap_files(tmp, tmp->next);
			tmp = begin;
		}
		else
			tmp = tmp->next;
	}
	tmp = begin;
	while (tmp && tmp->name)
	{
		if (!(!(op & 16) && tmp->name[0] == '.'))
		{
			(op & 1) ? get_stat(ft_strjoin(str, tmp->name)) : 0;
			ft_printf(" %s", tmp->name);
			op ? ft_printf("\n") : 0;
		}
		tmp = tmp->next;
	}
	tmp = begin;
	while (tmp)
	{
		if ((op & 8) && tmp->type == 4 && ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
			recc(ft_strjoin(str, tmp->name), op);
		tmp = tmp->next;
	}
}

void	recc(char *str, char op)
{
	t_ls	*begin;
	t_ls	*list;
	DIR		*dire;
	struct dirent* dir;

	dire = opendir(str);
	if (!dire)
	{
		perror(str);
		return ;
	}
	mallcheck(list = (t_ls*)ft_memalloc(sizeof(t_ls)));
	begin = list;
	op & 12 ? ft_printf("\n%s:\n", str) : 0;
	str = ft_strjoin(str, "/");
	while ((dir = readdir(dire)) != NULL)
	{
		mallcheck(list->next = (t_ls*)ft_memalloc(sizeof(t_ls)));
		list->next->prev = list;
		list->type = dir->d_type;
		list->name = ft_strdup(dir->d_name);
		list = list->next;
	}
	sort_files(begin, str, op);
	closedir(dire);
}

int		main(int ac, char **av)
{
	parse_input(ac,av);
	return 0;
}
