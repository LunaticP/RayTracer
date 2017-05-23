# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsimeon <gsimeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2017/05/23 23:54:52 by pgourran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRC_NAME =	main.c\
			key.c\
			key_f.c\
			texture.c\
			perlin.c\
			langton.c\
			message_info.c\
			parse_text.c\
			vec.c\
			img.c\
			dsr.c\
			bmp/ft_bmp_file_load.c\
			bmp/ft_bmp_to_ubmp.c\
			bmp/get_ppm.c\
			bmp/load.c\
			bmp/memjoin.c\
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
			rt_list_to_tab.c\
			rt_parser_textures.c\
			rt_atoi.c\
			rt_parser_settings.c\
			rt_get_str.c\
			rt_get_float3_init.c\
			rt_check_value.c\
			rt_get_float4_end.c\
			rt_get_float4_neg.c\

INC_FILE = include/key.h\
		   include/obj.h\
		   include/rt_bmp.h\
		   include/parser.h\
		   include/rt.h

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC = gcc
OBJ_SUB =	network\
			bmp


INC=-I./include -I./libft -I./rt_win/includes -I./mmlx/includes -I./libmatrix -I ./libocl
ARG=-L./libft/ -L./rt_win -L./libmatrix -L./libocl \
	-lft -lmatrix -lrt_win -locl \
	-framework OpenGl -framework AppKit -framework opencl
CFLAGS = -Wall -Wextra -Werror
DEPDIR				= .deps/
DEPFILES			= $(patsubst %.c,$(DEPDIR)%.d,$(SRC_NAME))

all: $(NAME)
	@printf "\t\t\e[32m[OK]\e[0m\n"

# Auto dependency generator
$(DEPDIR)/%.d: $(SRC_PATH)%.c $(DEPDIR)%.d
	@mkdir -p $(DEPDIR)
	@$(CC) $(CFLAGS) $(INC) -MM -MT $(DEPDIR)$(patsubst %.c,$(DEPDIR)%.d,$(notdir $@)) $< -MF $@

# Add dependency as prerequisites
-include $(DEPFILES)

$(NAME): lib print_rt $(OBJ)
	@$(CC) -g -O0 $(CFLAGS) $(ARG) $(INC) $(OBJ) -o $@
lib:
	@make -C ./libft
	@make -C ./libmatrix
	@make -C ./libocl
	@make -C ./rt_win

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILE)
	-@mkdir -p $(OBJ_PATH) $(addprefix $(OBJ_PATH),$(OBJ_SUB))
	@$(CC) $(CFLAGS) -c -o $@ $< $(INC)

clean:
	-@rm -rf $(OBJ_PATH) $(DEPDIR)
	@make -C ./libft $@
	@make -C ./libmatrix $@
	@make -C ./libocl $@
	@make -C ./rt_win $@
	@printf "\e[33mobjects\t\t\e[31m[CLEAN]\e[0m\n"

fclean: clean
	-@rm $(NAME)
	@make -C ./libft $@
	@make -C ./libmatrix $@
	@make -C ./libocl $@
	@make -C ./rt_win $@
	@printf "\e[33m$(NAME)\t\t\e[31m[CLEAN]\e[0m\n"

re: fclean all

print_rt:
	@printf "\e[33m$(NAME)"

test: all
	./$(NAME) ./button_plus.bmp

.PHONY: all fclean clean re 
