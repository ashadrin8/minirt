
# Universal Makefile for minirt
NAME = minirt
NAME_C = minirt.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
INCLUDES = -Iincludes -Ilibft/libft -Ilibft/printf -Ilibft/gnl

# List all source files (add new files here as needed)
SRC_FILES = \
	src/parsing/parsing.c \
	src/parsing/parse_objects.c \
	src/parsing/initialization.c \
	src/parsing/color_parsing.c \
	src/parsing/coordinates_parsing.c \
	src/parsing/utils.c \
	libft/gnl/get_next_line.c \
	libft/gnl/get_next_line_utils.c

# Build directory for object files
BUILD_DIR = build

# Generate object file paths in build/, preserving source structure
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# List all needed build subdirectories
BUILD_DIRS = $(sort $(dir $(OBJ_FILES)))

# Static libraries
LIBFT = libft/libft/libft.a
PRINTF = libft/printf/printf.a

# Default target
all: $(NAME)

# Link the executable
$(NAME): $(LIBFT) $(PRINTF) $(BUILD_DIRS) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) $(NAME_C) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "\033[1;32mBuild complete! 🎉\033[0m"

# Create build subdirectories as needed
$(BUILD_DIRS):
	@mkdir -p $@

# Pattern rule: compile any .c file from any subdirectory into build/
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build static libraries
$(LIBFT):
	$(MAKE) -C libft/libft

$(PRINTF):
	$(MAKE) -C libft/printf

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C libft/libft clean
	$(MAKE) -C libft/printf clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft/libft fclean
	$(MAKE) -C libft/printf fclean

re: fclean all

.PHONY: all clean fclean re