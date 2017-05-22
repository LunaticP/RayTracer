## Name of Project

NAME = librt_win.a

## Color for compilating (red)

GREY = \0033[1;30m
RED = \0033[0;31m
GREEN = \0033[0;32m
YELLOW = \0033[0;33m
BLUE = \0033[0;34m
PINK = \0033[0;35m
CYAN = \0033[0;36m
WHITE = \0033[0;37m
COLOR_OUT = \0033(B\0033[m

COLOR = $(GREY)
COLOR_MMLX = $(CYAN)

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs
MMLX_DIR = ../mmlx

## Compilating Utilities

MMLX_INC = $(MMLX_DIR:%=-I./%/includes)
EXTERN_INC = -I ../include -I ../libft
INC = $(INC_DIR:%=-I./%)

FLAGS = -Wall -Wextra -Werror

MMLX = $(MMLX_DIR:%=%/libmmlx.a)
CC = clang $(FLAGS) $(INC) $(MMLX_INC) $(EXTERN_INC)

## List of Functions/Files

SRC_FT = bc_decrease \
		bc_increase \
		bc_modify_pitch \
		bl_decr_flt \
		bl_incr_flt \
		bl_modify_pitch \
		bl_settings_cone \
		bl_settings_cylinder \
		bl_settings_default \
		bl_settings_sphere \
		bp_decrease_f \
		bp_increase_f \
		bp_modify_pitch \
		mod_color_block \
		mod_color \
		mod_pitch \
		rt_fclose \
		rt_fkeypress \
		rt_win_error \
		rt_win_redraw \
		rt_win_ftoa \
		rt_win_getpitch \
		sc_default \
		sl_color_int \
		sl_default_flt \
		sl_pitch_flt \
		sm_color_blue \
		sm_color_green \
		sm_color_red \
		sm_default_flt \
		str_get_color \
		str_get_value \
		str_get_switch \
		swc_basic \
		swl_basic_flt \
		swp_basic_f \
		win_create_cone \
		win_create_cylinder \
		win_create_plan \
		win_create_sphere

## List of Utilities

OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o)
SRC = $(SRC_FT:%=$(SRC_DIR)/%.c)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME)\t$(GREY)[All OK]$(COLOR_OUT)"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(COLOR)Creating    : $(GREEN)$@$(COLOR_OUT)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@
	@echo "$(COLOR)Compiled : $(GREEN)$(@:$(OBJ_DIR)/%=%)$(COLOR_OUT)"

$(MMLX):
	@echo "$(COLOR_MMLX)libmmlx.a\t$(YELLOW)[Make]$(COLOR_OUT)"
	@make -j -C $(MMLX_DIR)

$(NAME): $(SRC) $(MMLX) $(OBJ_DIR)
	@$(MAKE) -j $(OBJ)
	@echo "$(COLOR)Objects\t\t$(GREEN)[Created]$(COLOR_OUT)"
	@cp $(MMLX) $@
	@ar -rcs $@ $(OBJ)
	@echo "$(COLOR)$(NAME)\t$(GREEN)[Created]$(COLOR_OUT)"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -j -C $(MMLX_DIR)
	@echo "$(COLOR)Objects\t\t$(RED)[Deleted]$(COLOR_OUT)"

fclean: clean
	@rm -f $(NAME)
	@make aclean -j -C $(MMLX_DIR)
	@echo "$(COLOR)$(NAME)\t$(RED)[Deleted]$(COLOR_OUT)"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/

.PHONY: all clean fclean re norme
