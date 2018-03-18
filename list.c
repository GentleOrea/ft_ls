/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 11:22:45 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/18 15:42:07 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	pop_list(t_ls *file)
{
	if (file->prev)
		file->prev->next = file->next;
	if (file->next)
		file->next->prev = file->prev;
}

void	swap_files(t_ls *file2, t_ls *file1)
{
	t_ls	*tmp;

	file1->next ? file1->next->prev = file2 : 0;

	file2->prev ? file2->prev->next = file1 : 0;

	tmp = file1->next;
	file1->next = file2;
	file2->next = tmp;
	//dmaill(file2);

	file1->prev = file2->prev;
	file2->prev = file1;
}
