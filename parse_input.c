/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:31:34 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/21 18:34:26 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



int		sort_input(char **av, int op)
{
	int i = 0;
	t_global *g;
	t_ls *list;
	t_ls *begin;

	mallcheck(g = (t_global*)ft_memalloc(sizeof(t_global)));
	mallcheck(list = (t_ls*)ft_memalloc(sizeof(t_ls)));
	if (av[1])
		g->m = 1;
	g->b = 1;
	list->name = ft_strdup(av[i]);
	list->path = list->name;
	begin = list;
	if (path_is_valid(g, av[i], &list->stat))
		get_stat(g, list);
	while (av[++i])
	{
		mallcheck(list = (t_ls*)ft_memalloc(sizeof(t_ls)));
		list->name = ft_strdup(av[i]);
		list->path = list->name;
		path_is_valid(g, av[i], &list->stat) ? get_stat(g, list) : 0;
		list = true_sort(begin, list, op);
		begin = list ? list : begin;
	}
	begin->b = 1;
	sort_files(g, begin, NULL, op);
	return (0);
}

int		parse_input(int ac, char **av)
{
	int			i;
	int			i2;
	int			op;
	t_global	g;

	i = 0;
	op = 0;
	while (++i < ac && av[i][0] == '-'  && av[i][1] && ft_strcmp(av[i], "--"))
	{
		i2 = 0;
		while (ft_isin(av[i][++i2], LS_FLAGS))
		{
			int dec = charchr(av[i][i2], LS_FLAGS);
			//if (dec == 2048 || dec == 16 || dec == 512 || dec == 1024)

			op |= 1 << dec;
		}
		if (av[i][i2])
		{
			ft_printf("Usage : ls [CGRalrt] [file ...]\n");
			return (1) ;
		}
	}
	!ft_strcmp(av[i], "--") ? ++i : 0; 
	ft_bzero(&g, sizeof(g));
	if (i == ac)
		recc(".", op, NULL);
	else
		sort_input(&av[i], op);
	//ft_printf("%d\n", temp);
	return (0);
	while (i < ac)
	{
		//op |= 0x80000000 : 0;

		//		recc(ft_strdup(av[i++]), op, NULL);
		//i < ac ? ft_printf("\n") : 0;
	}
	//ft_printf("%d\n", op);
	return (0);
}
