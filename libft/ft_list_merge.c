/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:54:52 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/11 17:02:59 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *fresh;

	if (!(begin_list1 && begin_list2))
		return ;
	fresh = *begin_list1;
	while (fresh->next)
		fresh = fresh->next;
	while (begin_list2->next)
	{
		fresh = begin_list2;
		fresh = fresh->next;
		begin_list2 = begin_list2->next;
	}
	fresh->next = NULL;
}
