# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviau <aviau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2017/05/05 11:40:56 by vthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = APPLE
NAME = rtvocl
SRC_NAME =	main.c\
			key.c\
			texture.c\
			useclustering.c\
			init_clustering.c\
			network/ft_sleep.c\
			network/create/create_server.c\
			network/create/getserver.c\
			network/create/init_client.c\
			network/create/serverthread.c\
			network/create/show_serverinfo.c\
			network/client/client.c

INC_FILE = include/key.h\
		   include/rt.h

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

OBJ_SUB = network\
		  network/create\
		  network/client


MLX=libmlx
INC=-I./include -I./libft -I./libmlx -I./libmatrix -I ./libocl
ARG=-L./libft/ -L./libmlx/ -L./libmatrix -L./libocl \
	-lft -lmatrix -lmlx -locl \
	-framework OpenGl -framework AppKit -framework opencl\
	-lpthread
CFLAGS = -Wall -Wextra
DEPDIR				= .deps/
DEPFILES			= $(patsubst %.c,$(DEPDIR)%.d,$(SRC_NAME))

ifeq ($(OS), LINUX)
all:
	@make -f Makefile_linux
clean:
	@make clean -f Makefile_linux
fclean:
	@make fclean -f Makefile_linux
re:
	@make re -f Makefile_linux
else
all: $(NAME)
	@printf "\t\t\e[32m[OK]\e[0m\n"
#linux:
#	make -f Makefile_linux
# Auto dependency generator
$(DEPDIR)/%.d: $(SRC_PATH)%.c $(DEPDIR)%.d
	@mkdir -p $(DEPDIR)
	@$(CC) $(CFLAGS) $(INC) -MM -MT $(DEPDIR)$(patsubst %.c,$(DEPDIR)%.d,$(notdir $@)) $< -MF $@

# Add dependency as prerequisites
-include $(DEPFILES)

$(NAME): lib print_rt $(OBJ)
	@gcc -g -O0 $(CFLAGS) $(ARG) $(INC) $(OBJ) -o $@
lib:
	@make -C ./$(MLX)
	@make -C ./libft
	@make -C ./libmatrix
	@make -C ./libocl
#lib:
#	@make -C ./libft
#	@make -C ./libmatrix
$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILE)
	-@mkdir -p $(OBJ_PATH) $(addprefix $(OBJ_PATH),$(OBJ_SUB))
	@gcc $(CFLAGS) -c -o $@ $< $(INC)

clean:
	-@rm -rf $(OBJ_PATH) $(DEPDIR)
	@make -C ./$(MLX) $@
	@make -C ./libft $@
	@make -C ./libmatrix $@
	@make -C ./libocl $@
	@printf "\e[33mobjects\t\t\e[31m[CLEAN]\e[0m\n"

fclean: clean
	@rm $(NAME)
	@make -C ./libft $@
	@make -C ./libmatrix $@
	@make -C ./libocl $@
	@printf "\e[33mrtvocl\t\t\e[31m[CLEAN]\e[0m\n"

re: fclean all

print_rt:
	@printf "\e[33mrtvocl"

test: all
	./$(NAME) ~/Downloads/tex/small.ppm
endif
.PHONY: fclean clean
