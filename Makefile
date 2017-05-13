# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviau <aviau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2017/05/13 19:18:56 by vthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = APPLE
NAME = rtvocl
SRC_NAME =	main.c\
			key.c\
			message_info.c\
			parse_text.c\
			perlin.c\
			texture.c\
			bmp/ft_bmp_file_load.c\
			bmp/ft_bmp_to_ubmp.c\
			bmp/get_ppm.c\
			bmp/load.c\
			network/broadcast.c\
			network/error.c\
			network/init_clustering.c\
			network/listener.c\
			network/memjoin.c\
			network/putimg.c\
			network/render.c\
			network/send_message.c\
			network/server.c\
			network/todo.c

INC_FILE = include/key.h\
		   include/rt.h

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

OBJ_SUB =	network\
			bmp


MLX=libmlx
INC=-I./include -I./libft -I./libmlx -I./libmatrix -I ./libocl
ARG=-L./libft/ -L./libmlx/ -L./libmatrix -L./libocl \
	-lft -lmatrix -lmlx -locl \
	-framework OpenGl -framework AppKit -framework opencl\
	-lpthread
CFLAGS =	-Wall -Wextra -g\
			-D USE_CLUSTER=0
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
	@make -C ./rt_win
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
	-@rm $(NAME)
	@make -C ./libft $@
	@make -C ./libmatrix $@
	@make -C ./libocl $@
	@printf "\e[33mrtvocl\t\t\e[31m[CLEAN]\e[0m\n"

re: fclean all

print_rt:
	@printf "\e[33mrtvocl"

test: all
	./$(NAME) ~/Downloads/tex/small.ppm ./button_plus.bmp
endif
.PHONY: fclean clean
