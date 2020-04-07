# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcharity <bcharity@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 10:49:23 by bcharity          #+#    #+#              #
#    Updated: 2020/02/03 15:50:24 by bcharity         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =  ft_atoi.c ft_bzero.c ft_isascii.c ft_isalnum.c  ft_isalpha.c ft_isdigit.c ft_isprint.c ft_memccpy.c\
		ft_memchr.c  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c ft_strcat.c ft_strchr.c\
		ft_strcmp.c  ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c\
		ft_strnstr.c  ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c\
	   	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striteri.c ft_striter.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c\
		ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c\
		ft_lstmap.c ft_freemem.c ft_strreverse.c ft_strcopyuntil.c ft_lstdel_contentsize.c \
		ft_lstcheck_contentsize.c ft_countwords_withnullstr.c ft_strndup.c ft_stack_fun.c \
		ft_reverse_int.c get_next_line.c \
		ft_vecnew.c ft_veccnt.c ft_vecadd.c ft_vecset.c ft_vecget.c \
		ft_vecgetfirst.c ft_vecgetlast.c ft_vecdel.c ft_vecfree.c ft_vecsel.c

SRC_DIR = src/

OBJ = $(patsubst %.c,%.o,$(SRCS))

OBJ_DIR_COMMON = obj/
OBJ_DIR = $(OBJ_DIR_COMMON)o_libft/

FLAGS = -Wall -Wextra -Werror
HEADER_DIR = includes/

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc -c $< -o $@ -I $(HEADER_DIR)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ))
	 @ar rcs $(NAME) $(addprefix $(OBJ_DIR),$(OBJ))

clean:
	@rm -Rf $(OBJ_DIR_COMMON)

fclean: clean
	@rm -f $(NAME);

re: fclean all
