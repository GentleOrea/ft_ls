/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:12:30 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/18 15:39:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_ls *tmp)
{
	while (tmp)
	{
		ft_printf("%s ", tmp->name);
		tmp= tmp->next;
	}
	ft_printf("\n");
}

void	dmaill(t_ls *maillon)
{
	if (!maillon)
		return ; 
	ft_printf("%s<-%s->%s\n", maillon->prev ? maillon->prev->name : 0,maillon->name, maillon->next ? maillon->next->name:0 );
}
