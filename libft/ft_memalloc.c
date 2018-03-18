/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:10:54 by ygarrot           #+#    #+#             */
/*   Updated: 2017/12/07 11:28:00 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	i = -1;
	if (size > 9223372036854775807)
		return (NULL);
	if (!(mem = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	while (++i < size + 1)
		((unsigned char*)mem)[i] = '\0';
	return (mem);
}
