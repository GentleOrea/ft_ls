/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:08:51 by ygarrot           #+#    #+#             */
/*   Updated: 2017/11/15 16:13:39 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_to_end(t_list **begin_list, void *content)
{
	t_list *list;
	t_list *elem;

	if (!begin_list)
		return ;
	list = *begin_list;
	if (!(elem = ft_lstnew(content, sizeof(content))))
		return ;
	while (list->next)
		list = list->next;
	list->next = elem;
}
