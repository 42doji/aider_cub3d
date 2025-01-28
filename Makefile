CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = cub3D

# Basic target definitions
all: $(NAME)

# Execution file build target
$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/include -I $(GNL_DIR)/include -c cub3D.c $(OBJ) -o $(NAME) -lm

# libft build target
$(LIBFT):
	make -C $(LIBFT_DIR)

# get_next_line build target
$(GNL):
-make -C $(GNL_DIR)

# Objects files generation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/include -I $(GNL_DIR)/include -c $< -o $@

# Objects directory creation rule
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean target
clean:
	rm -rf $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/include -I $(GNL_DIR)/include -c cub3D.c $(OBJ) -o $(NAME) -lm
	rm -f $(NAME)

# Full clean target
fclean: clean
	rm -rf $(NAME)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/include -I $(GNL_DIR)/include -c cub3D.c $(OBJ) -o $(NAME) -lm
	rm -f $(NAME)

# Recompute target
re: fclean all

# Additional targets
.PHONY: all clean fclean re
```