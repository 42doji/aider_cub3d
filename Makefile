NAME = test_gnl

LIBFT_PATH = ../../libft
GNL_PATH = ../../get_next_line
INCLUDES = -I$(LIBFT_PATH) -I$(GNL_PATH)
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -DBUFFER_SIZE=42

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(GNL_PATH) -lgnl

$(LIBFT):
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
