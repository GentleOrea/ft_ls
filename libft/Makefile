# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 14:29:56 by ygarrot           #+#    #+#              #
#    Updated: 2018/03/12 10:25:10 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

INCLUDES = includes/

SRC = 	ft_lstadd.c ft_memdel.c ft_strcat.c \
		ft_strlcat.c ft_strsplit.c ft_lstdel.c ft_memmove.c ft_strchr.c \
		ft_strlen.c ft_strstr.c ft_lstdelone.c ft_memset.c ft_strclr.c \
		ft_strmap.c ft_strsub.c ft_atoi.c ft_lstiter.c ft_putchar.c \
		ft_strcmp.c ft_strmapi.c ft_strtrim.c ft_bzero.c ft_lstmap.c \
		ft_putchar_fd.c ft_strcpy.c ft_strncat.c ft_tolower.c ft_isalnum.c \
		ft_lstnew.c ft_putendl.c ft_strdel.c ft_strncmp.c ft_toupper.c \
		ft_isalpha.c ft_memalloc.c ft_putendl_fd.c ft_strdup.c ft_strncpy.c \
		ft_isascii.c ft_memccpy.c ft_putnbr.c ft_strequ.c ft_strnequ.c \
		ft_isdigit.c ft_memchr.c ft_putnbr_fd.c ft_striter.c ft_strnew.c \
		ft_isprint.c ft_memcmp.c ft_putstr.c ft_striteri.c ft_strnstr.c \
		ft_itoa.c ft_memcpy.c ft_putstr_fd.c ft_strjoin.c ft_strrchr.c \
		ft_list_last.c ft_list_at.c ft_list_push_params.c ft_add_to_end.c \
		ft_list_merge.c ft_int_isin.c ft_free_dblechar_tab.c ft_isin.c\
		ft_free_dblechar_tab.c ft_free_dblint_tab.c ft_init_char_tab.c\
		ft_init_int_tab.c ft_print_chartab.c ft_print_inttab.c ft_strndup.c\
		ft_int_isin.c ft_strisin_tab.c ft_capitalize.c ft_ismin.c ft_ismax.c\
		ft_strisin.c ft_abs.c ft_itoa_base.c ft_imaxtoa_base.c \
		ft_uimaxtoa_base.c get_next_line.c ft_realloc.c ft_tablen.c\
		ft_str_isdigit.c ft_initdbl_int_tab.c ft_print_dbl_inttab.c\
		ft_putnbr_recc.c ft_search_char.c chooseconv.c convuimax.c convs.c\
		ft_printf.c parser_printf.c parsecolor.c printp.c print_nchar.c\
		ft_occur_in.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c $(INCLUDES)/libft.h
	@gcc -o $@ $(FLAGS) -c $< -I $(INCLUDES)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
