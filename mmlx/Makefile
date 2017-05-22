## Name of Project

NAME = libmmlx.a

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

COLOR = $(BLUE)
COLOR_MLX = $(PINK)

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs
MLX_DIR = minilibx_macos

## External Sources

LINK_ELCAPITAN = https://projects.intra.42.fr/uploads/document/document/287/minilibx_macos_20151105.tgz
LINK_SIERRA = https://projects.intra.42.fr/uploads/document/document/356/minilibx_macos_sierra_20161017.tgz

MLX_LINK = $(LINK_ELCAPITAN)

## Compilating Utilities

MLX_INC = $(MLX_DIR:%=-I./%)
INC = $(INC_DIR:%=-I./%)

FLAGS = -Wall -Wextra -Werror

MLX = $(MLX_DIR:%=%/libmlx.a)
CC = clang $(FLAGS) $(INC) $(MLX_INC)

## List of Functions/Files

SRC_FT = ml_memcpy \
		ml_memdel \
		ml_memset \
		ml_putendl_fd \
		ml_putstr_fd \
		ml_strdel \
		ml_strdup \
		mmlx_button_flyed \
		mmlx_button_link \
		mmlx_button_pressed \
		mmlx_button_released \
		mmlx_button_unlink \
		mmlx_button_update \
		mmlx_buttontype_create \
		mmlx_close \
		mmlx_create_child \
		mmlx_create_id \
		mmlx_create_parent \
		mmlx_create_win \
		mmlx_cursorpos_update \
		mmlx_data_fill \
		mmlx_error \
		mmlx_get_parent \
		mmlx_init_tmlx \
		mmlx_inside_data_button \
		mmlx_keypress \
		mmlx_keyrelease \
		mmlx_mouse_press \
		mmlx_mouse_release \
		mmlx_mouse_xy \
		mmlx_onbutton \
		mmlx_onslider \
		mmlx_onswitch \
		mmlx_refresh \
		mmlx_slider_catched \
		mmlx_slider_link \
		mmlx_slider_pressed \
		mmlx_slider_released \
		mmlx_slider_unlink \
		mmlx_slider_update \
		mmlx_slidertype_create \
		mmlx_string_create \
		mmlx_string_remove \
		mmlx_string_update \
		mmlx_switch_link \
		mmlx_switch_pressed \
		mmlx_switch_unlink \
		mmlx_switch_update \
		mmlx_switchtype_create

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

$(MLX):
	@rm -rf $(MLX_DIR)
	@echo "$(COLOR_MLX)mlx\t\t$(YELLOW)[Downloading]$(CYAN)"
	@curl -o MLX $(MLX_LINK)
	@echo "$(COLOR_MLX)mlx\t\t$(GREEN)[Downloaded]$(CYAN)"
	@echo "$(COLOR_MLX)mlx\t\t$(YELLOW)[Extracting]$(CYAN)"
	@tar -xf MLX && rm -r MLX
	@echo "$(COLOR_MLX)mlx\t\t$(GREEN)[Extracted]$(CYAN)"
	@echo "$(COLOR_MLX)mlx\t\t$(YELLOW)[Make]$(CYAN)"
	@make -j -C $(MLX_DIR)
	@cp -f $(MLX_DIR:%=%/mlx.h) $(INC_DIR)
	@echo "$(COLOR_MLX)libmlx.a\t$(GREEN)[Created]$(COLOR_OUT)"

$(NAME): $(SRC) $(MLX) $(OBJ_DIR)
	@$(MAKE) -j $(OBJ)
	@echo "$(COLOR)Objects\t\t$(GREEN)[Created]$(COLOR_OUT)"
	@cp $(MLX) $@
	@ar -rcs $@ $(OBJ)
	@echo "$(COLOR)$(NAME)\t$(GREEN)[Created]$(COLOR_OUT)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)Objects\t\t$(RED)[Deleted]$(COLOR_OUT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME)\t$(RED)[Deleted]$(COLOR_OUT)"

aclean: fclean
	@rm -rf $(MLX_DIR)
	@rm -f $(INC_DIR:%=%/mlx.h)
	@echo "$(COLOR)$(MLX_DIR)\t$(RED)[Deleted]$(COLOR_OUT)"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/

.PHONY: all clean fclean aclean re norme
