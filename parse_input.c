/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:31:34 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/18 10:25:42 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_input(int ac, char **av)
{
	int		i;
	int		i2;
	int		op;

	i = 1;
	op = 0;
	while (i < ac && av[i][0] == '-')
	{
		i2 = 0;
		while (ft_isin(av[i][++i2], LS_FLAGS))
			op |= 1 << charchr(av[i][i2], LS_FLAGS);
		if (av[i++][i2])
		{
			ft_printf("Usage : ls [CGRalrt] [file ...]\n");
			return ;
		}
	}
	while (i < ac)
		recc(av[i++], op);
	if (ac == 1)
		recc(".", op);
	ft_printf("%d\n", op);
}
