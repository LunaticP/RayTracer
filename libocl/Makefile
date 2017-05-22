# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vthomas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/21 20:30:16 by vthomas           #+#    #+#              #
#    Updated: 2017/05/21 20:30:20 by vthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= libocl.a
SHELL	= /bin/sh
RM		= /bin/rm

ARFLAG	= rcs
CC		= gcc
CFLAG	= -Wall -Werror -Wextra
OBJ		= $(SRC:.c=.o)
SRC		= ocl_enqueue_kernel.c \
		ocl_finish.c \
		ocl_get_karg.c \
		ocl_kernel_init.c \
		ocl_new_kernel.c \
		ocl_new_prog.c \
		ocl_struct_init.c \
		ocl_error.c \
		ocl_build_prog.c \
		ocl_get_right_kernel.c \
		ocl_free_kernel.c \
		ocl_set_memobj.c

I		= $$(($(words $(SRC)) / 2))
K		= $$(($(I) * 2 + 1))
n ?= $(I)
j ?= $(K)

all: swag $(NAME)
	@printf "\033[33mLIBOCL\033[0m\t\t\t\t\t\t\t\t   [\033[92mDONE\033[39m]\n"
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
	@echo "LIBOCL"
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
