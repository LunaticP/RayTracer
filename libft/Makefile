# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 21:57:41 by pgourran          #+#    #+#              #
#    Updated: 2017/05/18 17:50:42 by gsimeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	= libft.a
SHELL	= /bin/sh
RM		= /bin/rm

ARFLAG	= rcs
CC		= gcc
CFLAG	= -Wall -Werror -Wextra
OBJ		= $(SRC:.c=.o)
SRC		= ft_atoi.c\
		  ft_bzero.c\
		  ft_isalnum.c\
		  ft_isalpha.c\
		  ft_isascii.c\
		  ft_isdigit.c\
		  ft_isprint.c\
		  ft_itoa.c\
		  ft_memalloc.c\
		  ft_memchr.c\
		  ft_memcmp.c\
		  ft_memcpy.c\
		  ft_memccpy.c\
		  ft_memdel.c\
		  ft_memmove.c\
		  ft_memset.c\
		  ft_putchar.c\
		  ft_putchar_fd.c\
		  ft_putendl.c\
		  ft_putendl_fd.c\
		  ft_putnbr.c\
		  ft_putnbr_fd.c\
		  ft_putstr.c\
		  ft_putstr_fd.c\
		  ft_strjoin.c\
		  ft_strjoinfree.c\
		  ft_strcat.c\
		  ft_strchr.c\
		  ft_strclr.c\
		  ft_strcmp.c\
		  ft_strcpy.c\
		  ft_strdel.c\
		  ft_strdup.c\
		  ft_strequ.c\
		  ft_striter.c\
		  ft_striteri.c\
		  ft_strlcat.c\
		  ft_strlen.c\
		  ft_strmap.c\
		  ft_strmapi.c\
		  ft_strncat.c\
		  ft_strncmp.c\
		  ft_strncpy.c\
		  ft_strnequ.c\
		  ft_strnew.c\
		  ft_strnstr.c\
		  ft_strrchr.c\
		  ft_strstr.c\
		  ft_strsub.c\
		  ft_strsubfree.c\
		  ft_strtrim.c\
		  ft_tolower.c\
		  ft_toupper.c\
		  ft_strsplit.c\
		  ft_sizeint.c\
		  ft_pow.c\
		  ft_lstadd.c\
		  ft_lstdel.c\
		  ft_lstdelone.c\
		  ft_lstiter.c\
		  ft_lstmap.c\
		  ft_lstnew.c\
		  ft_isprime.c\
		  ft_sqrt.c\
		  ft_puttab.c\
		  ft_lstlen.c\
		  get_next_line.c\
		  ft_lstpushback.c\
		  ft_put_array.c\
		  ft_put_tab_array.c\
		  ft_freeinttab.c\
		  get_file.c\
		  ft_lsttotab.c\
		  pf_itoa.c

I		= $$(($(words $(SRC)) / 2))
K		= $$(($(I) * 2 + 1))
n ?= $(I)
j ?= $(K)

all: swag $(NAME)
	@printf "\033[33mLIBFT\033[0m\t\t\t\t\t\t\t\t   [\033[92mDONE\033[39m]\n"
	@j=$(j); \
	while [ $${j} -gt 0 ] ; do \
	printf "-"; \
	j=`expr $$j - 1`; \
	done; \
	true
	@echo ""

swag:
	@j=$(j); \
	while [ $${j} -gt 0 ] ; do \
	printf "-"; \
	j=`expr $$j - 1`; \
	done; \
	true
	@echo ""
	@n=$(n); \
	while [ $${n} -gt 0 ] ; do \
	printf " "; \
	n=`expr $$n - 1`; \
	done; \
	true
	@echo "LIBFT"
	@j=$(j); \
	while [ $${j} -gt 0 ] ; do \
	printf "-"; \
	j=`expr $$j - 1`; \
	done; \
	true
	@echo ""
	@printf "\033[32;7m"

$(NAME): $(OBJ)
	@echo "\033[0m"
	@printf "\033[33mBIN\033[0m\t\t\t\t\t\t\t       [\033[92mCOMPILED\033[39m]\n"
	@ar $(ARFLAG) $(NAME) $(OBJ)
#	@echo "$(NAME) is: OK"
%.o: %.c
	@printf " "
	@$(CC) $(CFLAG) -I includes -o $@ -c $<

clean:
	@rm -rf $(OBJ)
#	@echo "clean obj: done"

fclean: clean
	@rm -rf $(NAME)
#	@echo "clean $(NAME): done"

re: fclean all
