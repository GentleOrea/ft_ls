/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:39:50 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/21 18:18:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	mallcheck(void *str)
{
	if (str)
		return ;
	ft_printf("Erreur de malloc\n");
	exit(EXIT_FAILURE);
}

void	ls_error(char *str)
{
	(void)str;
	perror("ls: fts_open");
}
