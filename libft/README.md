# libft

# LIBFT 프로젝트 소개

**libft**는 **첫번째** 본과정 **프로젝트**로

**Libft - C Standard Library**의 문자열을 다루는 기초 함수들을 

스스로 작성하여 다른 프로젝트에서 사용할 수 있도록 라이브러리로 만드는 것입니다.

### 깃허브 링크

https://github.com/42doji/libft

### 배운 것.

- **man 페이지**를 검색하여 함수를 조사하기
- **테스트 케이스**를 작성하기
- ar 유틸리티와 컴파일 명령어를 이용해 **library**를 만드는 방법
- 기초적인 **Makefile** 문법
- 메모리 **동적 할당** 및 해제
- **valgrind**를 이용해 **메모리 누수**를 관리하기
- gcc 디버거를 이용한 **디버깅**
- 기초 자료구조 : **링크드 리스트**

### 핵심 코드

라이브러리를 만들기 위해서

Makefile의 문법과 기초적인 쉘스크립트에 대한 공부

그리고 c언어를 컴파일하는 과정에 대한 이해가 필요했습니다.

```makefile
NAME = libft
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = -rcs
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	ar $(ARFLAGS) $(NAME).a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(OBJS_BONUS)
	ar $(ARFLAGS) $(NAME).a $(OBJS) $(OBJS_BONUS)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(SRCS_BONUS)
	gcc -nostartfiles -shared -o $(NAME).so $(OBJS) $(OBJS_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME).a $(NAME).so

re: fclean all

.PHONY: all, clean, fclean, re
```

### ft_split.c

문자열과 구분자를 입력값으로 받아서

새로운 문자열 배열로 단어를 쪼갠 후 반환하는 함수.

반환해야할 문자열의 갯수를 세어 동적 할당하며

또다시 문자열 각각의 문자수를 세어 동적 할당한 뒤

복사를 해야하는 함수로 가장 어려운 도전이었습니다.

```c
#include "libft.h"

static void	ft_allocate(char **tab, char const *s, char sep)
{
	char		**tab_p;
	char const	*tmp;

	tmp = s;
	tab_p = tab;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		while (*tmp && *tmp != sep)
			++tmp;
		if (*tmp == sep || tmp > s)
		{
			*tab_p = ft_substr(s, 0, tmp - s);
			s = tmp;
			++tab_p;
		}
	}
	*tab_p = NULL;
}

static int	ft_count_words(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++word_count;
		while (*s && *s != sep)
			++s;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	ft_allocate(new, s, c);
	return (new);
}

```

### Libft 함수

**<ctype.h>의 함수**
ft_isalpha - 알파벳 문자를 확인합니다.
ft_isdigit - 숫자(0~9)를 확인합니다.
ft_isalnum - 영숫자 문자인지 확인합니다.
ft_isascii - c가 ASCII 문자 집합에 맞는지 확인합니다.
ft_isprint - 인쇄 가능한 문자인지 확인합니다.
ft_toupper - 문자를 대문자로 변환합니다.
ft_tolower - 문자를 소문자로 변환합니다.
<string.h>의 함수
ft_memset - 메모리를 상수 바이트로 채웁니다.
ft_strlen - 문자열의 길이를 계산합니다.
ft_bzero - 바이트 문자열을 0으로 만듭니다.
ft_memcpy - 메모리 영역 복사.
ft_memmove - 메모리 영역 복사.
ft_strlcpy - 문자열을 특정 크기로 복사합니다.
ft_strlcat - 문자열을 특정 크기로 연결합니다.
ft_strchr - 문자열에서 문자 찾기.
ft_strrchr - 문자열에서 문자 찾기.
ft_strncmp - 두 문자열을 비교합니다.
ft_memchr - 메모리에서 문자를 검색합니다.
ft_memcmp - 메모리 영역 비교.
ft_strnstr - 문자열에서 하위 문자열을 찾습니다.
ft_strdup - 매개변수로 전달된 문자열에 대한 복제본을 만듭니다.
<stdlib.h>의 함수
ft_atoi - 문자열을 정수로 변환합니다.
ft_calloc - 메모리를 할당하고 해당 바이트 값을 0으로 설정합니다.

**비표준 함수**
ft_substr - 문자열에서 부분 문자열을 반환합니다.
ft_strjoin - 두 문자열을 연결합니다.
ft_strtrim - 특정 문자 집합으로 문자열의 시작과 끝을 잘라냅니다.
ft_split - 문자를 매개변수로 사용하여 문자열을 분할합니다.
ft_itoa - 숫자를 문자열로 변환합니다.
ft_strmapi - 문자열의 각 문자에 함수를 적용합니다.

ft_striteri - 문자열의 각 문자에 함수를 적용합니다.
ft_putchar_fd - 파일 디스크립터에 문자를 출력합니다.
ft_putstr_fd - 파일 디스크립터에 문자열을 출력합니다.
ft_putendl_fd - 문자열을 파일 디스크립터에 출력한 다음 새 줄을 출력합니다.
ft_putnbr_fd - 파일 디스크립터에 숫자를 출력합니다.

**링크드 리스트 함수**
ft_lstnew - 새 목록 요소를 만듭니다.
ft_lstadd_front - 목록의 시작 부분에 요소를 추가합니다.
ft_lstsize - 목록의 요소 수를 계산합니다.
ft_lstlast - 목록의 마지막 요소를 반환합니다.
ft_lstadd_back - 목록 끝에 요소를 추가합니다.
ft_lstclear - 목록을 삭제하고 비웁니다.
ft_lstiter - 목록의 각 요소에 함수를 적용합니다.
ft_lstmap - 목록의 각 요소에 함수를 적용합니다.
