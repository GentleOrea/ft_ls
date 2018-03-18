/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:13:28 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/23 13:57:15 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int		i;
	char	*ch;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (!(ch = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		ch[i] = src[i];
		i++;
	}
	ch[i] = '\0';
	return (ch);
}
