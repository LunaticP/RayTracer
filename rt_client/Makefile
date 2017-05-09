# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviau <aviau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2017/05/09 11:49:23 by aviau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
OS = APPLE
NAME = rt_client
SRC_NAME =	main.c\
			callback.c\
			client.c\
			create_client.c\
			error.c\
			init_network.c\
			listener.c\
			memjoin.c\
			message_info.c\
			send_message.c
INC_FILE = include/rt.h

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

MLX=libmlx
INC=-I./include -I./libft -I./libmatrix -I ./libocl
ARG=-L./libft/ -L./libmatrix -L./libocl \
	-lft -lmatrix -locl \
	-framework opencl -lpthread
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
	@make -C ./libft
	@make -C ./libmatrix
	@make -C ./libocl
#lib:
#	@make -C ./libft
#	@make -C ./libmatrix
$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILE)
	-@mkdir -p $(OBJ_PATH)
	@gcc $(CFLAGS) -c -o $@ $< $(INC)

clean:
	-@rm -rf $(OBJ_PATH) $(DEPDIR)
	@make -C ./libft $@
	@make -C ./libmatrix $@
	@make -C ./libocl $@
	@printf "\e[33mobjects\t\t\e[31m[CLEAN]\e[0m\n"

fclean: clean
	-@rm $(NAME)
	-@make -C ./libft $@
	-@make -C ./libmatrix $@
	-@make -C ./libocl $@
	@printf "\e[33mrtvocl\t\t\e[31m[CLEAN]\e[0m\n"

re: fclean all

print_rt:
	@printf "\e[33mrtvocl"

test : CFLAGS = -Wall -Wextra -g
test: all
	./$(NAME) 127.0.0.1
endif
.PHONY: fclean clean
