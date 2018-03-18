/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:17:40 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/10 13:40:35 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uimaxtoabase(uintmax_t value, int base)
{
	uintmax_t	result;
	int			i;
	char		*str;

	i = 0;
	result = value;
	while (result /= base)
		i++;
	if (!(str = (char*)malloc((i + (value ? 1 : 0) + 1) * sizeof(char))))
		return (NULL);
	str[0] = value ? '\0' : '0';
	str[i + 1] = '\0';
	while (value > 0)
	{
		str[i--] = ((value % base) < 10) ?
			(value % base) + '0' : (value % base) - 10 + 'a';
		value /= base;
	}
	return (str);
}
