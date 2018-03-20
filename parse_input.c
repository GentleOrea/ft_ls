/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:31:34 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/20 19:01:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	int temp = 0;
	if (i + 1 < ac)
		temp = 1;
	//ft_printf("%d\n", temp);
	while (i < ac)
	{
		temp ? op |= 0x80000000 : 0;
		recc(ft_strdup(av[i++]), op, NULL);
		i < ac ? ft_printf("\n") : 0;
	}
		//ft_printf("%d\n", op);
	return (0);
}
