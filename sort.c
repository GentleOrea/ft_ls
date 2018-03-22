/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:43:27 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/22 15:44:05 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_terms(t_ls *begin, t_ls *to_add, int op)
{
	if (op & 65536)
		return (0);
	if (op & 0x800 && !(op & 8))
		return (to_add->stat.st_atime >= begin->stat.st_atime);
	else if (op & 0x800)
		return (to_add->stat.st_atime <= begin->stat.st_atime);
	else if (op & 16 && !(op & 8))
		return (to_add->stat.st_mtime > begin->stat.st_mtime);
	else if (op & 16)
		return (to_add->stat.st_mtime <= begin->stat.st_mtime);
	else if (op & 512 && !(op & 8))
		return (to_add->stat.st_size > begin->stat.st_size);
	else if (op & 512)
		return (to_add->stat.st_size <= begin->stat.st_size);
	else if (op & 0x40 && !(op & 8))
		return (to_add->stat.st_ctime > begin->stat.st_ctime);
	else if (op & 0x40)
		return (to_add->stat.st_ctime <= begin->stat.st_ctime);
	else if (!(op & 8))
		return (ft_strcmp(begin->name, to_add->name) > 0);
	return (ft_strcmp(begin->name, to_add->name) < 0);
}

t_ls	*true_sort(t_ls *begin, t_ls *to_add, int op)
{
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
	if (!begin->next)
	{
		begin->next = to_add;
		return (NULL);
	}
	to_add->next = begin->next;
	begin->next = to_add;
	return (NULL);
}


