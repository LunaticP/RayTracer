# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2017/04/27 06:21:13 by pgourran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = APPLE
NAME = rtvocl
SRC_NAME =	main.c\
			key.c\
			texture.c\
			rt_get_char.c\
			rt_get_color.c\
			rt_get_float.c\
			rt_get_float2.c\
			rt_get_float3.c\
			rt_get_float4.c\
			rt_get_int_2.c\
			rt_get_short.c\
			rt_get_str_float.c\
			rt_end_data.c\
			rt_goto_close_bracket.c\
			exit_error.c\
			folder_mask.c\
			rt_free_after_parser.c\
			rt_memalloc.c\
			rt_strcmp.c\
			rt_useless.c\
			parser_error.c\
			rt_get_file.c\
			rt_get_object.c\
			rt_parser_camera.c\
			rt_parser_file.c\
			rt_parser_lights.c\
			rt_parser_objects.c\
			parser.c\
			rt_list_to_tab.c

INC_FILE = include/key.h\
		   include/rt.h\
		   include/parser.h

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

MLX=libmlx
INC=-I./include -I./libft -I./libmlx -I./libmatrix -I ./libocl
ARG=-L./libft/ -L./libmlx/ -L./libmatrix -L./libocl \
	-lft -lmatrix -lmlx -locl \
	-framework OpenGl -framework AppKit -framework opencl
CFLAGS = -Wall -Wextra -Werror
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
	-@mkdir -p $(OBJ_PATH)
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
endif
.PHONY: fclean clean
