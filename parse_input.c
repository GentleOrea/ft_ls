/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:31:34 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/22 20:10:02 by ygarrot          ###   ########.fr       */
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
	if (av[1])
		g->m = 1;
	g->b = 1;
	while (av[i] && !(begin = path_is_valid(g, ft_strdup(av[i]), NULL, op)))
		i++;
	if (!begin)
		return (0);
	list = begin;
	list->name = ft_strdup(list->path);
	while (av[++i])
	{
		if ((list = path_is_valid(g, ft_strdup(av[i]), NULL, op)))
		{
			list->name = ft_strdup(list->path);
			list = true_sort(begin, list, op);
			begin = list ? list : begin;
		}
	}
	begin->b = 1;
	sort_files(g, begin, NULL, op);
	return (0);
}

void manage_op(int *op)
{
	(void)op;
	if (*op & 0x40 || *op & 0x400 || *op & 0x2000)
		*op |= 0x1;
	if (*op & 0x4)
		*op &= 0xFFFF7FFF;
	if (*op & 0x1000 || *op & 0x8000)
		*op |= 4;
}

int		parse_input(int ac, char **av)
{
	int			i;
	int			i2;
	int			op;
	int			dec;
	i = 0;
	op = 0;
	while (++i < ac && av[i][0] == '-'  && av[i][1] && ft_strcmp(av[i], "--"))
	{
		i2 = 0;
		while (ft_isin(av[i][++i2], LS_FLAGS))
		{
			dec = 1 << charchr(av[i][i2], LS_FLAGS);
			if (dec & 0x20 && op & 0x2041)
				op &= 0xFFFFDFBE;
			if (dec & 0x2041 && op & 0x20)
				op &= 0xFFFFFFEF;
			op |= dec;
		}
		if (av[i][i2])
		{
			ft_printf("Usage : ls [CGRalrt] [file ...]\n");
			return (1) ;
		}
	}
	!ft_strcmp(av[i], "--") ? ++i : 0;
	//ft_printf("%#x\n", op);
	manage_op(&op);
	if (i == ac)
		recc(".", op, NULL);
	else
		sort_input(&av[i], op);
	return (0);
}
