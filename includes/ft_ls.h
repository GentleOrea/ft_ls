/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:14:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/18 15:39:35 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# define LS_FLAGS "lGCRart"

typedef struct s_ls
{
	char		type;
	char		path;
	char		*name;
	struct s_ls *next;
	struct s_ls *prev;
	struct stat stat;
}				t_ls;

void	dmaill(t_ls *maillon);
void	print_list(t_ls *tmp);
void	pop_list(t_ls *file);
void	swap_files(t_ls *file1, t_ls *file2);
void	parse_input(int ac, char **av);
void	mallcheck(void *crap);
void	recc(char *str, char op);
#endif
