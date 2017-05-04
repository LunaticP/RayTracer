# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 14:25:33 by vthomas           #+#    #+#              #
#    Updated: 2017/05/04 10:23:27 by vthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=serveur
CC = clang
CFLAGS = -Wall -Wextra -g -Os -Ofast
#CFLAGS =

PARAMS = 8327

DBG_OUT = /dev/null

SRC_NAME = main.c\
		   error.c\
		   client.c\
		   create_sendclient.c\
		   create_server.c\
		   message.c\
		   searchclient.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = ./src/
OBJ_PATH = ./obj/

OBJ_SUB =

SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

LIB = -L ./libft -lft -lpthread
INC = -I ./include -I ./libft
FMW =

all: $(NAME)

$(NAME): lib $(OBJ)
	@printf "\033[34;1m\n▶    \033[0;32;1m✔ \033[0;34;1mSources\033[0;32;1m ✔\033[0;34;1m    ◀\033[0m\n"
	@printf "\033[90m--------------------------------------------------------------------------------\033[0m\n"
	@printf "\033[34m▶    \033[4mLINK\033[0;34m    ◀\033[0m\n"
	@$(CC) $(OBJ) $(CFLAGS) $(LIB) $(INC) $(FMW) -o $@
	@chmod +x $(NAME)
	@printf "\033[34;1m\n▶    \033[0;32;1m✔ \033[0;34;1mLink\033[0;32;1m ✔\033[0;34;1m    ◀\033[0m\n"
	@printf "\033[90m--------------------------------------------------------------------------------\033[0m\n"

lib:
	@clear
	@printf "\033[34m▶    \033[4mLIBRAIRIES\033[0;34m    ◀\033[0m\n"
	@printf "\033[32;4m▶\tLIBFT\033[0m\n"
	@make -C ./libft
	@printf "\033[34;1m\n▶    \033[0;32;1m✔ \033[0;34;1mLibrairies\033[0;32;1m ✔\033[0;34;1m    ◀\033[0m\n"
	@printf "\033[90m--------------------------------------------------------------------------------\033[0m\n"
	@printf "\033[34m▶    \033[4mSOURCES\033[0;34m    ◀\033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH) $(addprefix $(OBJ_PATH),$(OBJ_SUB))
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	-@rm -rf $(OBJ_PATH);
	@make -C ./libft $@

fclean: clean
	-@rm $(NAME)
	@make -C ./libft $@
	@printf "🦄  There is no more unicorn poop 🦄\n"

re: fclean all

test: all
	@clear
	@clear > $(DBG_OUT)
	./$(NAME) $(PARAMS) 2> $(DBG_OUT)
.PHONY: fclean clean
