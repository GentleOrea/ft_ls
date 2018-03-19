/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:14:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/19 18:28:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

#include <sys/ioctl.h>
# define LS_FLAGS "lRartACFGScu1imn"
//# define LS_FLAGS "FlGCRacirtu1"

typedef struct	s_global
{
	int		op;
	int		s_len;
	int		l_len;
	int		g_len;
	int		u_len;
	DIR		*dire;
	struct dirent *dir;
	int		nb_block;
}				t_global;

typedef struct s_ls
{
	char		type;
	char		*path;
	char		*name;
	char		*uid;
	char		*gid;
	struct stat stat;
	struct s_ls *next;
	struct s_ls *prev;
}				t_ls;

void	dmaill(t_ls *maillon);
void	print_list(t_ls *tmp);
void	pop_list(t_ls *file);
void	swap_files(t_ls *file1, t_ls *file2);
void	parse_input(int ac, char **av);
void	mallcheck(void *crap);
void	recc(char *str, int op);
void	get_stat(t_global*g, t_ls *list, char *argv);
void	print_stat(t_global *g, t_ls *list);
#endif
