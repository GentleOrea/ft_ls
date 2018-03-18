/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:43:33 by ygarrot           #+#    #+#             */
/*   Updated: 2017/11/15 16:21:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	unsigned int	i;
	t_list			*fresh;

	i = 0;
	if (!(begin_list && nbr))
		return (NULL);
	fresh = begin_list;
	while (begin_list->next && i < nbr)
	{
		fresh = fresh->next;
		i++;
	}
	return (fresh);
}
