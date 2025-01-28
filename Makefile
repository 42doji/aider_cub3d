CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Additional dependencies
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = get_next_line
GNL_SRCS = $(wildcard $(GNL_DIR)/*.c)
GNL_OBJS = $(patsubst $(GNL_DIR)/%.c, $(OBJ_DIR)/%.o, $(GNL_SRCS))

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = cub3D

# Default target
all: $(NAME)

# Build executable
$(NAME): $(LIBFT) $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(GNL_DIR) \
		$(OBJS) $(GNL_OBJS) $(LIBFT) -o $(NAME) -lm

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Build get_next_line object files
$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(GNL_DIR) -c $< -o $@

# Create object directory if not exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re
