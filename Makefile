# ==============================
# Project Name
# ==============================
NAME = miniRT
NAME_C = minirt.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE -Wunreachable-code -Ofast #-lm #-fsanitize=address -g

#SHELL := /bin/bash
#export PATH := /opt/homebrew/bin:/usr/local/bin:$(PATH)

# ==============================
# Includes
# ==============================
INCLUDES    = -I includes \
              -I libft/libft \
              -I libft/printf \
              -I libft/gnl \
              -IMLX42/include

# ==============================
# Sources
# ==============================
SRC_FILES = \
	minirt.c \
	src/parsing/parsing.c \
	src/parsing/parse_objects.c \
	src/parsing/initialization.c \
	src/parsing/color_parsing.c \
	src/parsing/coordinates_parsing.c \
	src/parsing/utils.c \
	src/render/render_scene.c \
	src/render/camera.c \
	src/render/window.c \
	src/render/utils.c \
	src/render/light.c \
	src/render/shadow.c \
	src/render/sphere.c \
	src/render/plane.c \
	src/render/cylinder.c \
	src/render/cone.c \
	src/render/vector_utils.c \
	src/vector_math/vector_math.c \
	libft/gnl/get_next_line.c \
	libft/gnl/get_next_line_utils.c

BUILD_DIR = build
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
BUILD_DIRS = $(sort $(dir $(OBJ_FILES)))

# ==============================
# Libraries
# ==============================
LIBFT = libft/libft/libft.a
PRINTF = libft/printf/printf.a

LIBMLX      = MLX42
MLX_BUILD   = $(LIBMLX)/build
MLX_LIB     = $(MLX_BUILD)/libmlx42.a
MLX_LIBS    = $(MLX_LIB) -ldl -lglfw -pthread -lm

# ==============================
# Default target
# ==============================
all: libmlx $(NAME)

# ==============================
# Build project
# ==============================
$(NAME): $(LIBFT) $(PRINTF) $(BUILD_DIRS) $(OBJ_FILES) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(PRINTF) $(MLX_LIBS) -o $(NAME)
	@echo "\033[1;32mBuild complete! 🎉\033[0m"

# ==============================
# Build object files
# ==============================
$(BUILD_DIRS):
	@mkdir -p $@
# Pattern rule: compile any .c file from any subdirectory into build/
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ==============================
# Build external libraries
# ==============================
$(LIBFT):
	$(MAKE) -C libft/libft

$(PRINTF):
	$(MAKE) -C libft/printf

# Build MLX42
libmlx: $(MLX_LIB)
$(MLX_LIB):
	@if [ ! -d "$(LIBMLX)" ] || [ -z "$$(ls -A $(LIBMLX) 2>/dev/null)" ]; then \
		git submodule update --init --recursive $(LIBMLX); \
	fi
	cmake $(LIBMLX) -B $(MLX_BUILD)
	$(MAKE) -C $(MLX_BUILD) -j4

# ==============================
# Clean
# ==============================
clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C libft/libft clean
	$(MAKE) -C libft/printf clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft/libft fclean
	$(MAKE) -C libft/printf fclean

re: fclean all

.PHONY: all clean fclean re libmlx
