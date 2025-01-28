#include "cub3d.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h"

static int row = 0;

int parse_map(t_game *game, const char *line)
{
    // 빈 라인 무시
    if (line[0] == '\0')
        return 0;

    // 메모리 할당 및 맵 그리드에 라인 추가
    game->map.grid[row] = strdup(line);
    if (!game->map.grid[row])
        return -1;
    row++;

    return 0;
}

int init_parser(t_game *game, const char *file_path)
{
    char *line;
    int fd = open(file_path, O_RDONLY);
    int ret;

    if (fd < 0)
    {
        perror("Error opening file");
        return -1;
    }

    // 맵의 최대 행 수 추정
    game->map.rows = 0;
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        game->map.rows++;
        free(line);
    }
    free(line);
    close(fd);

    // 맵 그리드 메모리 할당
    game->map.grid = malloc(sizeof(char *) * (game->map.rows + 1));
    if (!game->map.grid)
        return -1;
    game->map.grid[game->map.rows] = NULL;

    // 다시 파일 열기
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error reopening file");
        return -1;
    }

    // 맵 파싱
    row = 0;
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (parse_map(game, line) == -1)
        {
            free(line);
            close(fd);
            return -1;
        }
        free(line);
    }
    close(fd);

    // 플레이어 초기 위치 및 방향 설정
    for (int y = 0; y < game->map.rows; y++)
    {
        for (int x = 0; game->map.grid[y][x] != '\0'; x++)
        {
            if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S' ||
                game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
            {
                game->player_x = x + 0.5;
                game->player_y = y + 0.5;
                if (game->map.grid[y][x] == 'N')
                {
                    game->dir_x = 0;
                    game->dir_y = -1;
                }
                else if (game->map.grid[y][x] == 'S')
                {
                    game->dir_x = 0;
                    game->dir_y = 1;
                }
                else if (game->map.grid[y][x] == 'E')
                {
                    game->dir_x = 1;
                    game->dir_y = 0;
                }
                else if (game->map.grid[y][x] == 'W')
                {
                    game->dir_x = -1;
                    game->dir_y = 0;
                }
                game->map.grid[y][x] = '0'; // 플레이어 위치를 빈 공간으로 변경
                break;
            }
        }
    }

    return 0;
}
