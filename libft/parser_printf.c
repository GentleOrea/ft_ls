/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsndprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 14:33:13 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/17 15:12:35 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		charchr(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return ((str[i] && str[i] == c) ? i : -1);
}

int		initlist(t_arg *list)
{
	int i;

	i = 0;
	while (i < 5)
		list->flags[i++] = 0;
	list->specifier = -1;
	list->conv = -1;
	list->att = -1;
	list->fg = -1;
	list->bg = -1;
	list->champ = 0;
	list->pre = -1;
	return (1);
}

int		get_fields(const char *str, int i, t_arg *tempm, int index)
{
	while (charchr(str[i], NBR) >= 0)
	{
		if (tempm->pre && str[i] == '.' && i++)
		{
			tempm->pre = 0;
			while (charchr(str[i], NBR) >= 0)
				tempm->pre = (tempm->pre * 10) + str[i++] - '0';
		}
		else
			tempm->champ = (tempm->champ * 10) + str[i++] - '0';
	}
	if ((index = charchr(str[i], SPECIFIER)) >= 0)
	{
		if (!index && !charchr(str[i + 1], SPECIFIER) && (i += 2))
			tempm->specifier = index;
		else if (index == 1 && charchr(str[i + 1], SPECIFIER) == 1 && (i += 2))
			tempm->specifier = index + 1;
		else if (i++)
		{
			index += (index < 1) ? 1 : 2;
			tempm->specifier = index;
		}
	}
	return (i);
}

int		parse_arg(const char *str, t_arg *tempm)
{
	int		i;
	int		index;

	i = 1;
	index = 0;
	while (str[i] && charchr(str[i], FLAGS) >= 0)
		tempm->flags[charchr(str[i++], FLAGS)] = 1;
	i = get_fields(str, i, tempm, index);
	if (charchr(str[i], CONVERT) >= 0 || str[i] == '%')
	{
		if (str[i] == '%')
			tempm->conv = 14;
		else
			tempm->conv = charchr(str[i], CONVERT);
		if (tempm->pre < 0 && tempm->conv < 10)
			tempm->pre = 1;
		return (i);
	}
	return (0);
}
