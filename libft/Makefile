# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/10 21:34:05 by vthomas           #+#    #+#              #
#    Updated: 2016/10/27 16:21:40 by vthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft
SRC_PATH = ./src/
SRC_NAME = list/ft_lstadd.c\
		   list/ft_lstdel.c\
		   list/ft_lstdelone.c\
		   list/ft_lstiter.c\
		   list/ft_lstmap.c\
		   list/ft_lstnew.c\
		   math/ft_abs.c\
		   math/ft_pow.c\
		   math/ft_tpow.c\
		   mem/ft_bzero.c\
		   mem/ft_memalloc.c\
		   mem/ft_memccpy.c\
		   mem/ft_memchr.c\
		   mem/ft_memcmp.c\
		   mem/ft_memcpy.c\
		   mem/ft_memdel.c\
		   mem/ft_memmove.c\
		   mem/ft_memset.c\
		   mem/ft_memswitch.c\
		   print/ft_putchar.c\
		   print/ft_putchar_fd.c\
		   print/ft_putendl.c\
		   print/ft_putendl_fd.c\
		   print/ft_putnbr.c\
		   print/ft_putnbr_desc.c\
		   print/ft_putnbr_endl.c\
		   print/ft_putnbr_fd.c\
		   print/ft_putstr.c\
		   print/ft_putstr_fd.c\
		   str/char/ft_isalnum.c\
		   str/char/ft_isalpha.c\
		   str/char/ft_isascii.c\
		   str/char/ft_isdigit.c\
		   str/char/ft_isprint.c\
		   str/char/ft_tolower.c\
		   str/char/ft_toupper.c\
		   str/conv/ft_atoi.c\
		   str/conv/ft_itoa.c\
		   str/str/ft_freejoin.c\
		   str/str/ft_strcat.c\
		   str/str/ft_strchr.c\
		   str/str/ft_strclr.c\
		   str/str/ft_strcmp.c\
		   str/str/ft_strcpy.c\
		   str/str/ft_strdel.c\
		   str/str/ft_strdup.c\
		   str/str/ft_strequ.c\
		   str/str/ft_striter.c\
		   str/str/ft_striteri.c\
		   str/str/ft_strjoin.c\
		   str/str/ft_strlcat.c\
		   str/str/ft_strlen.c\
		   str/str/ft_strlower.c\
		   str/str/ft_strmap.c\
		   str/str/ft_strmapi.c\
		   str/str/ft_strncat.c\
		   str/str/ft_strncmp.c\
		   str/str/ft_strncpy.c\
		   str/str/ft_strnequ.c\
		   str/str/ft_strnew.c\
		   str/str/ft_strnstr.c\
		   str/str/ft_strrchr.c\
		   str/str/ft_strsplit.c\
		   str/str/ft_strstr.c\
		   str/str/ft_strsub.c\
		   str/str/ft_strtabdel.c\
		   str/str/ft_strtrim.c
OBJ_PATH = ./obj/
INC_PATH = ./
INC_NAME = libft.h
INC = $(addprefix -I, $(INC_PATH))
CC = clang
CFLAGS = -Werror -Wall -Wextra -Ofast -Os
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB_NAME = libft.a
LIB_PATH = ./
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))

all: $(NAME)
$(NAME): $(OBJ) $(LIB)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/list
	@mkdir -p $(OBJ_PATH)/math
	@mkdir -p $(OBJ_PATH)/mem
	@mkdir -p $(OBJ_PATH)/print
	@mkdir -p $(OBJ_PATH)/str
	@mkdir -p $(OBJ_PATH)/str/char
	@mkdir -p $(OBJ_PATH)/str/conv
	@mkdir -p $(OBJ_PATH)/str/str
	$(CC) $(CFLAGS) -c $(INC) -o $@ $<

$(LIB):
	@ar rc $@ $(OBJ)
	@ranlib $@

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(OBJ_PATH)
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(LIB)

re: fclean all

test: re
	@clear
	@$(CC) $(CFLAGS) $(INC) main.c $(LIB)
	@./a.out | cat -e
	@/bin/rm -rf a.out
	@(cd ./ && $(MAKE) fclean)

norme:
	@clear
	@norminette $(SRC) $(INC_PATH)*.h
.PHONY: fclean clean
