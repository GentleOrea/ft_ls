/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:23:29 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/17 13:25:13 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define FLAGS "+0- #"
# define NBR "0132456789."
# define SPECIFIER "hljz"
# define CONVERT "uoxUOXpdDicCsS"
# define BUFF_SIZE 32
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <wctype.h>
# include <stdarg.h>
# include <stdbool.h>
# include <wchar.h>
# include <limits.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_gnl
{
	char			*buf;
	int				fd;
	struct s_gnl	*next;
}				t_gnl;

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
t_list			*ft_lstnew(void const *content, size_t content_size);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memalloc(size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putchar(char c);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_strdel(char **as);
char			*ft_strdup(const char *src);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str1);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *dest, const char *src, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
char			*ft_strcpy(char *dst, const char *src);
int				ft_tolower(int c);
int				ft_toupper(int c);
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list			*ft_list_push_params(int ac, char **av);
t_list			*ft_list_last(t_list *begin_list);
void			ft_add_to_end(t_list **begin_list, void *content);
void			ft_list_merge(t_list **begin_list1, t_list *begin_list2);

void			ft_print_chartab(char **tab, int fd);
void			ft_print_inttab(int *tab, int size);
int				ft_isin(char c, char *str);
int				ft_int_isin(int tofind, int *tab, int size);
void			ft_free_dblechar_tab(char **tab);
void			ft_free_dblint_tab(int **tab, int size);
int				ft_strisin(char *tofind, char *str);
int				ft_strisin_tab(char *str, char **tab, int option);
int				**ft_init_char_tab(int size, int size2);
int				*ft_init_int_tab(int size);
void			ft_capitalize(char *str);
int				ft_ismax(int i, int i2);
int				ft_ismin(int i, int i2);
char			*ft_strndup(char *todup, size_t siz);
int				ft_abs(int value);
char			*ft_itoabase(int value, int base);
char			*ft_imaxtoabase(intmax_t value, int base);
char			*ft_uimaxtoabase(uintmax_t value, int base);
char			**ft_init_double_tab(int size, int size2);

int				get_next_line(const int fd, char **line);
void			*ft_realloc(void *str, size_t size);
int				ft_tablen(char **tab);
int				ft_str_isdigit(char *str);
int				**ft_initdbl_int_tab(size_t size1, size_t size2);
void			ft_print_dbl_inttab(int **tab, size_t size1, size_t size2);
int				ft_search_char(char *str, char c, int end);
void			ft_putnbr_recc(int nbr);

typedef struct	s_arg
{
	int		flags[5];
	int		specifier;
	int		conv;
	int		att;
	int		fg;
	int		bg;
	int		champ;
	int		pre;
	int		length;
	int		padding;
}				t_arg;

void			print1(char *str, t_arg *list);
int				parse_arg(const char *str, t_arg *list);
int				bin_count(wchar_t v);

char			*convwstr(wchar_t *str);
char			*convc(int dec);
char			*convwchar(wint_t dec);
char			*convim(intmax_t nb);
char			*convuim(uintmax_t nb);
char			*convuimo(uintmax_t nb);
char			*convuimx(uintmax_t nb);

char			*convsigned(va_list va, t_arg *list);
char			*convunsigned(va_list va, t_arg *list);
int				*putf(va_list va, t_arg *list, const char *str, int *i);

char			*chooseconv(va_list va, t_arg *list);

void			colorise(t_arg *list);
int				parse_colors(char *str, t_arg *list);
void			reset_int_tab(int *i, int row);

int				ft_printf(const char *first, ...);
void			ft_putn_schar(char c, int nb);
void			ft_putnstr(char *str, size_t nb, t_arg *list);
int				initlist(t_arg *list);
int				charchr(char c, char *str);
int				ft_occur_in(char *str, char c);

int				get_next_line_lst(int fd, char **line);
#endif
