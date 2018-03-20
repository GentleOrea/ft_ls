/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:18:39 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/20 18:46:47 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

void	sort_files(t_global *g, t_ls *begin, char *str, int op)
{
	t_ls	*tmp;
	t_ls	*to_del;
	char	link[256];

	ft_bzero(link, sizeof(link));
	tmp = begin;
	(op & 1) ? ft_printf("total %d\n", g->nb_block) : 0;
	while (tmp && tmp->name)
	{
		if (!(!(op & 4) && tmp->name[0] == '.'))
		{
			(op & 1) ? print_stat(g, tmp) : 0;
			ft_printf("%s", tmp->name);
			readlink(tmp->path, link, 255) > 0 && (op & 1)? ft_printf(" -> %s", link) : 0;
			ft_printf("\n");
		}
		tmp = tmp->next;
	}
	tmp = begin;
	while (tmp)
	{
		if ((op & 2) && tmp->type == 4 && ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
		{
			ft_printf("\n");
			op & 2 ? ft_printf("%s:\n", tmp->path = ft_strjoin(str, tmp->name)) : 0;
			(void)str;
			recc(tmp->path, op, tmp);
		}
		to_del = tmp;
		tmp = tmp->next;
		ft_memdel((void**)&to_del->name);
		ft_memdel((void**)&to_del->path);
		ft_memdel((void**)&to_del);
	}
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

	if (!(g->dir = readdir(g->dire)))
		return (begin) ;
	begin->type = g->dir->d_type;
	begin->name = ft_strdup(g->dir->d_name);
	get_stat(g, begin, begin->path = ft_strjoin(str, begin->name));
	while ((g->dir = readdir(g->dire)))
	{
		if (!(!(op & 4) && g->dir->d_name[0] == '.'))
		{
			mallcheck(tmp = (t_ls*)ft_memalloc(sizeof(t_ls)));
			get_stat(g, tmp, tmp->path = ft_strjoin(str, g->dir->d_name));
			tmp = true_sort(begin, tmp, op);
			tmp ? begin = tmp : 0;
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
	op & 0x80000000 ? ft_printf(g->dire ? "%s:\n" : "%s", str) : 0;
	if (!g->dire)
	{
		char *temp = ft_strjoin("ls: ", actual ? actual->name : str);
		!(op & 0x80000000) ? perror(temp) : 0;
		//ft_memdel((void**)&str);
		return ;
	}
	op &= 0x7FFFFFFF;
	mallcheck(begin = (t_ls*)ft_memalloc(sizeof(t_ls)));
	str = ft_strjoin(str, "/");
	begin = sort_files2(g, begin, str, op);
	sort_files(g, begin, str, op);
	ft_memdel((void**)&str);
	closedir(g->dire);
	ft_memdel((void**)&g);
}

int		main(int ac, char **av)
{
	return (parse_input(ac,av));
}
