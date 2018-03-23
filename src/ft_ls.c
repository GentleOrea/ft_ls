/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:18:39 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/23 14:29:34 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	end_sort(t_global *g, t_ls *tmp, char *str, int op)
{
	t_ls	*to_del;

	while (tmp)
	{
		if ((g->b && (tmp->stat.st_mode & S_IFMT) == S_IFDIR) ||
				((op & 2) && tmp->type == 4 && ft_strcmp(tmp->name, ".")
				 && ft_strcmp(tmp->name, "..")))
		{
			!tmp->path ? tmp->path = ft_strjoin(str, tmp->name) : 0;
			!tmp->b ? ft_printf("\n") : 0;
			(!g->b && op & 2) || (g->b && g->m && op & 2) || (g->b && g->m) ?
				ft_printf("%s:\n", tmp->path) : 0;
			recc(tmp->path, op, tmp);
		}
		to_del = tmp;
		tmp = tmp->next;
		ft_memdel((void**)&to_del->uid);
		ft_memdel((void**)&to_del->gid);
		ft_memdel((void**)&to_del->name);
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
		if ((((((op & 0x8000) && ft_strcmp(tmp->name, ".")
								&& ft_strcmp(tmp->name, "..")) || !(op & 0x8000)) && !g->b && !(!(op & 4) &&
							tmp->name[0] == '.')) || (g->b && (tmp->stat.st_mode & S_IFMT) != S_IFDIR)))
		{
			(op & 1) ? print_stat(g, tmp, op) : 0;
			ft_printf("%s", tmp->name);
			if (readlink(tmp->path, link, 255) > 0 && (op & 1))
				ft_printf(" -> %s", link);
			ft_printf("\n");
			begin->b = 0;
		}
		tmp = tmp->next;
	}
	end_sort(g, begin, str, op);
}

t_ls	*sort_files2(t_global *g, char *str, int op)
{
	t_ls	*tmp;
	t_ls	*begin;

	begin = NULL;
	while (!begin && (g->dir = readdir(g->dire)))
		begin = path_is_valid(g, str, g->dir->d_name, op);
	while ((g->dir = readdir(g->dire)))
		if ((tmp = path_is_valid(g, str, g->dir->d_name, op)))
		{
			tmp = true_sort(begin, tmp, op);
			tmp ? begin = tmp : 0;
		}
	return (begin);
}

void	recc(char *str, int op, t_ls *actual)
{
	t_ls		*begin;
	t_global	g;

	ft_bzero(&g, sizeof(g));
	g.dire = opendir(str);
	if (!g.dire)
	{
		ls_error(actual ? actual->name : str);
		return ;
	}
	str = ft_strjoin(str, "/");
	begin = sort_files2(&g, str, op);
	begin ? sort_files(&g, begin, str, op) : 0;
	ft_memdel((void**)&str);
	closedir(g.dire);
}

int		main(int ac, char **av)
{
	return (parse_input(ac, av));
}
