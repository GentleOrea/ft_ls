/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:57:02 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/23 13:51:04 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(char *str, size_t nb, t_arg *list)
{
	size_t	value;

	value = 0;
	if (!list)
		return ;
	if (str && !*str && (list->conv == 10 || list->conv == 11))
	{
		write(1, "\0", 1);
		return ;
	}
	if (!nb && !str)
	{
		if (list->pre)
			write(1, "(null)", 6);
		return ;
	}
	while (str[value] && value < nb)
		value++;
	write(1, str, value);
}

void	ft_putn_schar(char c, int nb)
{
	char	str[nb];
	int		temp;

	if (nb < 0)
		return ;
	temp = nb;
	while (temp)
		str[--temp] = c;
	write(1, str, (size_t)nb);
}
