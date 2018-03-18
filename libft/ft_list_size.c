/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:12:43 by ygarrot           #+#    #+#             */
/*   Updated: 2017/12/07 11:51:59 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size(t_list *begin_list)
{
	int		i;
	t_list	*temp;

	i = 0;
	if (!begin_list)
		return (0);
	temp = begin_list;
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	return (i + 1);
}
