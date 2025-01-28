#include "cub3d.h"

int init_parser(t_game *game, const char *file_path)
{
    char *line;
    int fd = open(file_path, O_RDONLY);

    if (fd < 0)
    {
        perror("Error opening file");
        return -1;
    }
    while (get_next_line(fd, &line) > 0)
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
    return 0;
}

int parse_map(t_game *game, const char *line)
{
    // 파싱 로직을 여기에 구현합니다.
    return 0;
}
