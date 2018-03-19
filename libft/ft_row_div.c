/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_row_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:39:39 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/19 16:46:19 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_row_div(int nb, int div)
{
	int i;

	i = 0;
	while (nb / div > 0)
	{
		nb /= div;
		i++;
	}
	return (i);
}
