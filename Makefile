# 컴파일러 및 플래그 설정
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# 디렉토리 설정
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# 소스 및 오브젝트 파일 설정
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# 실행 파일 이름
NAME = cub3d

# 기본 타겟
all: $(NAME)

# 실행 파일 생성
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# 오브젝트 파일 생성 규칙
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# 오브젝트 디렉토리 생성
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 클린 타겟
clean:
	rm -rf $(OBJ_DIR)

# 포맷 클린 타겟
fclean: clean
	rm -f $(NAME)

# 재빌드 타겟
re: fclean all

# 틀린 타겟 설정
.PHONY: all clean fclean re
