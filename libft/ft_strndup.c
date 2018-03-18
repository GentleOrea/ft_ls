/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:19:32 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/05 11:27:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(char *todup, size_t size)
{
	char *dupped;

	if (!todup || !size)
		return (NULL);
	size = ft_ismax(size, ft_strlen(todup));
	if (!(dupped = (char*)malloc(++size * sizeof(char))))
		return (NULL);
	dupped[size] = '\0';
	while (--size)
		dupped[size] = todup[size];
	return (dupped);
}
