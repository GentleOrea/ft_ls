/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:20:04 by ygarrot           #+#    #+#             */
/*   Updated: 2017/11/15 16:22:11 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_push_params(int ac, char **av)
{
	int		i;
	t_list	*temp;
	t_list	*begin;

	i = 0;
	temp = NULL;
	if (!(ac && av))
		return (NULL);
	if (!(temp = ft_lstnew(av[i], sizeof(av[i]))))
		return (NULL);
	temp = temp->next;
	begin = temp;
	while (i < ac)
	{
		if (!(temp = ft_lstnew(av[i], sizeof(av[i]))))
			return (NULL);
		temp = temp->next;
	}
	return (begin);
}
