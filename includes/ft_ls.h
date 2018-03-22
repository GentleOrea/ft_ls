/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:14:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/22 15:42:55 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
# define LS_FLAGS "lRartACFGScu1imnUf"

typedef struct	s_global
{
	char			b;
	char	m;
	int		op;
	char	m_files;
	int		s_len;
	int		l_len;
	int		g_len;
	int		u_len;
	int		min_len;
	int		maj_len;
	DIR		*dire;
	struct dirent *dir;
	int		nb_block;
}				t_global;

typedef struct s_ls
{
	char			b;
	char			type;
	char			*path;
	char			*name_f;
	char			*name;
	char			*uid;
	char			*gid;
	unsigned int	maj;
	int				min;
	struct stat stat;
	struct s_ls *next;
	struct s_ls *prev;
}				t_ls;

void	sort_files(t_global *g, t_ls *begin, char *str, int op);
t_ls	*true_sort(t_ls *begin, t_ls *to_add, int op);
void	dmaill(t_ls *maillon);
void	print_list(t_ls *tmp);
void	pop_list(t_ls *file);
void	swap_files(t_ls *file1, t_ls *file2);
int		parse_input(int ac, char **av);
void	mallcheck(void *crap);
void	recc(char *str, int op, t_ls *list);
void	get_stat(t_global*g, t_ls *list, int op);
void	print_stat(t_global *g, t_ls *list, int op);
void	ls_error(char *str);
t_ls	*path_is_valid(t_global *g, char *path, char *name, int op);
void	convert_mode(mode_t st_mode, t_ls *list);
#endif
