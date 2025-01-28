CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Additional dependencies
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = get_next_line
GNL = $(GNL_DIR)/gnl.a

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = cub3D

# Basic targets
all: $(NAME)

# Execution file build target
$(NAME): $(LIBFT) $(GNL) $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(GNL_DIR)/include \
		$(OBJS) $(LIBFT) $(GNL) -o $(NAME) -lm

# Library build targets
$(LIBFT): $(OBJS:$(SRCS)/%.c=libft.o)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(GNL_DIR)/include \
		$(OBJS) -c -o libft.o

$(GNL): $(OBJS:$(SRCS)/%.c=gnl.o)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(GNL_DIR)/include \
		$(OBJS) -c -o gnl.o

# Object file build target
$(OBJS): $(SRCS:$(SRC_DIR)/%.c=*.o)
	$(CC) $(CFLAGS) -c $< -o $@

# Directories creation targets
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean targets
clean:
	rm -rf $(OBJ_DIR)

re:
	finish

# Full clean target
fclean: clean
	rm -f $(NAME)
	finish

# Rebuild target
.PHONY: all clean fclean re
