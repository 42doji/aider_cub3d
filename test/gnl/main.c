#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;

	// 테스트 케이스 1: 일반 텍스트 파일 읽기
	fd1 = open("test_files/file1.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening file1.txt");
		return (1);
	}

	printf("=== Test Case 1: Reading file1.txt ===\n");
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	printf("\n");

	// 테스트 케이스 2: 빈 파일 읽기
	fd1 = open("test_files/empty_file.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening empty_file.txt");
		return (1);
	}

	printf("=== Test Case 2: Reading empty_file.txt ===\n");
	line = get_next_line(fd1);
	if (line == NULL)
		printf("No lines to read (NULL returned)\n");
	else
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	printf("\n");

	// 테스트 케이스 3: 매우 긴 라인이 있는 파일 읽기
	fd1 = open("test_files/long_line.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening long_line.txt");
		return (1);
	}

	printf("=== Test Case 3: Reading long_line.txt ===\n");
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	printf("\n");

	// 테스트 케이스 4: 여러 파일 디스크립터 동시에 읽기
	fd1 = open("test_files/file1.txt", O_RDONLY);
	fd2 = open("test_files/file2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error opening file1.txt or file2.txt");
		return (1);
	}

	printf("=== Test Case 4: Reading file1.txt and file2.txt simultaneously ===\n");
	while (1)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("fd1: %s", line);
			free(line);
		}
		else
			printf("fd1: [End of File]\n");

		line = get_next_line(fd2);
		if (line)
		{
			printf("fd2: %s", line);
			free(line);
		}
		else
			printf("fd2: [End of File]\n");

		if (!line && !get_next_line(fd1) && !get_next_line(fd2))
			break ;
	}
	close(fd1);
	close(fd2);
	printf("\n");

	// 테스트 케이스 5: 표준 입력에서 읽기
	printf("=== Test Case 5: Reading from standard input (type lines, press Ctrl+D to end) ===\n");
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		printf("You entered: %s", line);
		free(line);
	}
	printf("End of standard input.\n");

	// 테스트 케이스 6: 존재하지 않는 파일 열기
	printf("\n=== Test Case 6: Opening non-existent file ===\n");
	fd1 = open("test_files/non_existent.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening non_existent.txt");
	}
	else
	{
		while ((line = get_next_line(fd1)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		close(fd1);
	}

	return (0);
}
