/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:18:39 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/21 18:03:20 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

void	end_sort(t_global *g, t_ls *tmp, char *str ,int op)
{
	t_ls	*to_del;
	while (tmp)
	{
		if ((g->b && (tmp->stat.st_mode & S_IFMT) == S_IFDIR) ||
				((op & 2) && tmp->type == 4 && ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, "..")))
		{
			!tmp->path ? tmp->path = ft_strjoin(str, tmp->name) : 0;
			!tmp->b ? ft_printf("\n") : 0;
			(!g->b && op & 2) || (g->b && g->m && op & 2) || (g->b && g->m) ? ft_printf("%s:\n", tmp->path) : 0;
			recc(tmp->path, op, tmp);
		}
		to_del = tmp;
		tmp = tmp->next;
		//if (!to_del->b || (to_del->stat.st_mode & S_IFMT) != S_IFDIR)
		//	ft_memdel((void**)&to_del->name);
		ft_memdel((void**)&to_del->path);
		ft_memdel((void**)&to_del);
	}
}

void	sort_files(t_global *g, t_ls *begin, char *str, int op)
{
	t_ls	*tmp;
	char	link[256];

	ft_bzero(link, sizeof(link));
	tmp = begin;
	(op & 1) && !g->b ? ft_printf("total %d\n", g->nb_block) : 0;
	while (tmp && tmp->name)
	{
		if ((!g->b && !(!(op & 4) && tmp->name[0] == '.'))
				|| (g->b && (tmp->stat.st_mode & S_IFMT) != S_IFDIR))
		{
			(op & 1) ? print_stat(g, tmp) : 0;
			ft_printf("%s", tmp->name);
			readlink(tmp->path, link, 255) > 0 && (op & 1)? ft_printf(" -> %s", link) : 0;
			ft_printf("\n");
			begin->b = 0;
		}
		tmp = tmp->next;
	}
	end_sort(g, begin, str, op);
}

int		get_terms(t_ls *begin, t_ls *to_add, int op)
{
	if (op & 2048 && !(op & 8))
		return (to_add->stat.st_atime > begin->stat.st_atime);
	else if (op & 2048)
		return (to_add->stat.st_atime <= begin->stat.st_atime);
	else if (op & 16 && !(op & 8))
		return (to_add->stat.st_mtime > begin->stat.st_mtime);
	else if (op & 16){// ft_printf("%s->%d < %s->%d{green}%d{reset}\n",to_add->name, to_add->stat.st_mtime,begin->name,
		//	begin->stat.st_mtime, to_add->stat.st_mtime < begin->stat.st_mtime);
		return (to_add->stat.st_mtime <= begin->stat.st_mtime);}
	else if (op & 512 && !(op & 8))
		return (to_add->stat.st_size > begin->stat.st_size);
	else if (op & 512)
		return (to_add->stat.st_size <= begin->stat.st_size);
	else if (op & 1024 && !(op & 8))
		return (to_add->stat.st_ctime > begin->stat.st_ctime);
	else if (op & 1024)
		return (to_add->stat.st_ctime <= begin->stat.st_ctime);
	else if (!(op & 8))
		return (ft_strcmp(begin->name, to_add->name) > 0);
	return (ft_strcmp(begin->name, to_add->name) < 0);
}

t_ls	*true_sort(t_ls *begin, t_ls *to_add, int op)
{
	//print_list(begin);
	if (get_terms(begin, to_add, op))
	{
		to_add->next = begin;
		return (to_add);
	}
	else if (!begin->next || get_terms(begin->next, to_add, op))
	{
		if (begin->next)
			to_add->next = begin->next;
		begin->next = to_add;
		return (NULL);
	}
	while (begin->next && !get_terms(begin->next, to_add, op))
		begin = begin->next;
	//if (begin->next)
	//	ft_printf("{magenta}%s / %s{reset}\n", begin->next->name, to_add->name);
	if (!begin->next)
	{
		begin->next = to_add;
		return (NULL);
	}
	to_add->next = begin->next;
	begin->next = to_add;
	return (NULL);
}

t_ls	*sort_files2(t_global *g, t_ls *begin, char *str, int op)
{
	t_ls	*tmp;
	char		*path;
	struct stat	temp;

	while ((g->dir = readdir(g->dire)) && !begin->path)
		path_is_valid(g, begin->path = ft_strjoin(str, g->dir->d_name), &temp);
	get_stat(g, begin);
	while ((g->dir = readdir(g->dire)))
	{
		if (!(!(op & 4) && g->dir->d_name[0] == '.'))
		{
			if (path_is_valid(g, path = ft_strjoin(str, g->dir->d_name), &temp))
			{
				mallcheck(tmp = (t_ls*)ft_memalloc(sizeof(t_ls)));
				tmp->stat = temp;
				tmp->path = path;
				get_stat(g, tmp);
				tmp = true_sort(begin, tmp, op);
				tmp ? begin = tmp : 0;
			}
		}
	}
	return (begin);
}

void	recc(char *str, int op, t_ls *actual)
{
	t_ls	*begin;
	t_global	*g;

	mallcheck(g = (t_global*)ft_memalloc(sizeof(t_global)));
	g->dire = opendir(str);
	if (!g->dire)
	{
		char *temp = ft_strjoin("ls: ", actual ? actual->name : str);
		(void)temp;
		perror(temp);
		//ft_memdel((void**)&str);
		return ;
	}
	mallcheck(begin = (t_ls*)ft_memalloc(sizeof(t_ls)));
	str = ft_strjoin(str, "/");
	begin = sort_files2(g, begin, str, op);
	sort_files(g, begin, str, op);
	ft_memdel((void**)&str);
	closedir(g->dire);
	!g->b ? ft_memdel((void**)&g) : 0;
}

int		main(int ac, char **av)
{
	return (parse_input(ac,av));
}
