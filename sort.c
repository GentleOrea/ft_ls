/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:43:27 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/22 20:05:49 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		time_sort(t_ls *begin, t_ls *to_add, int op)
{
	if (op & 0x200 && !(op & 0x8))
		return (to_add->stat.st_atime >= begin->stat.st_atime);
	else if (op & 0x200)
		return (to_add->stat.st_atime <= begin->stat.st_atime);
	else if (op & 0x100 && !(op & 0x8))
		return (to_add->stat.st_ctime > begin->stat.st_ctime);
	else if (op & 0x100)
		return (to_add->stat.st_ctime <= begin->stat.st_ctime);
	else if (op & 0x800 && !(op & 0x8))
		return (to_add->stat.st_birthtime > begin->stat.st_birthtime);
	else if (op & 0x800)
		return (to_add->stat.st_birthtime <= begin->stat.st_birthtime);
	else if (!(op & 8))
		return (to_add->stat.st_mtime > begin->stat.st_mtime);
	return (to_add->stat.st_mtime <= begin->stat.st_mtime);
}

int		get_terms(t_ls *begin, t_ls *to_add, int op)
{
	//ft_printf("%d\n", op & 0x16);
	if (op & 0x1000)
		return (0);
	else if (op & 0x80 && !(op & 0x8))
		return (to_add->stat.st_size > begin->stat.st_size);
	else if (op & 0x80)
		return (to_add->stat.st_size <= begin->stat.st_size);
	else if (op & 16)
		return (time_sort(begin, to_add, op));
	else if (!(op & 0x8))
		return (ft_strcmp(begin->name, to_add->name) > 0);
	return (ft_strcmp(begin->name, to_add->name) <= 0);
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


