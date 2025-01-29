/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:43:57 by doji              #+#    #+#             */
/*   Updated: 2025/01/29 00:44:00 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../include/parser.h"
 #include "../libft/libft.h"

int check_file_extension(const char *filename)
{
    if (!filename)
    {
        ft_putendl_fd("Error: Filename is NULL.", 2);
        return (0);
    }

    const char *extension = ".cub";
    size_t len = ft_strlen(filename);
    size_t ext_len = ft_strlen(extension);

    if (len < ext_len)
    {
        ft_putendl_fd("Error: Filename is too short to have a valid extension.", 2);
        return (0);
    }

    int result = (ft_strncmp(&filename[len - ext_len], extension, ext_len) == 0);
    if (!result)
        ft_putendl_fd("Error: Invalid file extension. Expected .cub", 2);
    return result;
}

 int is_all_whitespace(char *line)
 {
     while (*line)
     {
         if (!ft_isspace(*line))
             return (0);
         line++;
     }
     return (1);
 }

 int is_configuration_line(char *line)
 {
     if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
         ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
         ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
         return (1);
     return (0);
 }

int parse_texture(char **texture, char *path)
{
    char *trimmed_path;

    trimmed_path = ft_strtrim(path, " \t\n");
    if (!trimmed_path)
    {
        ft_putendl_fd("Error: Memory allocation failed for texture path.", 2);
        return (0);
    }
    *texture = trimmed_path;
    printf("Parsed texture path: '%s'\n", *texture);
    return (1);
}

int parse_color(int *color, char *value)
{
    char **rgb;
    int r, g, b;

    char *trimmed_value = ft_strtrim(value, " \t\n");
    if (!trimmed_value)
    {
        ft_putendl_fd("Error: Memory allocation failed for color value.", 2);
        return (0);
    }
    rgb = ft_split(trimmed_value, ',');
    free(trimmed_value);
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
    {
        ft_putendl_fd("Error: Invalid color format. Expected format: R,G,B", 2);
        if (rgb)
        {
            for (int i = 0; rgb[i]; i++)
                free(rgb[i]);
            free(rgb);
        }
        return (0);
    }

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    for (int i = 0; rgb[i]; i++)
        free(rgb[i]);
    free(rgb);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        ft_putendl_fd("Error: Color values must be between 0 and 255.", 2);
        return (0);
    }

    *color = (r << 16) | (g << 8) | b;
    return (1);
}

 int handle_configuration_line(t_game *game, char *line)
 {
     printf("Handling configuration line: '%s'\n", line);
     if (ft_strncmp(line, "NO ", 3) == 0)
         return (parse_texture(&game->north_texture, line + 3));
     else if (ft_strncmp(line, "SO ", 3) == 0)
         return (parse_texture(&game->south_texture, line + 3));
     else if (ft_strncmp(line, "WE ", 3) == 0)
         return (parse_texture(&game->west_texture, line + 3));
     else if (ft_strncmp(line, "EA ", 3) == 0)
         return (parse_texture(&game->east_texture, line + 3));
     else if (ft_strncmp(line, "F ", 2) == 0)
         return (parse_color(&game->floor_color, line + 2));
     else if (ft_strncmp(line, "C ", 2) == 0)
         return (parse_color(&game->ceiling_color, line + 2));
     ft_putendl_fd("Error: Unknown configuration line.", 2);
     return (0);
 }

 int validate_configuration(t_game *game, int parsed_elements)
 {
     (void)game;

     if (parsed_elements < 6)
     {
         ft_putendl_fd("Error: Missing configuration elements.", 2);
         return (0);
     }
     // 추가 유효성 검사 필요
     return (1);
 }

 int parse_configuration(t_game *game, int fd)
 {
     char    *line;
     int     parsed_elements;

     parsed_elements = 0;
     while ((line = get_next_line(fd)) != NULL)
     {
         printf("Read line: '%s'\n", line);
         if (ft_strlen(line) == 0 || is_all_whitespace(line))
         {
             printf("Skipping empty or whitespace line.\n");
             free(line);
             continue;
         }
         if (is_configuration_line(line))
         {
             if (!handle_configuration_line(game, line))
             {
                 free(line);
                 return (0);
             }
             parsed_elements++;
         }
         else
         {
             printf("Non-configuration line encountered, stopping configuration parsing.\n");
             free(line);
             break;
         }
         free(line);
     }
     // Ensure the file descriptor is at the start of the map section
     while ((line = get_next_line(fd)) != NULL)
     {
         if (ft_strlen(line) > 0 && !is_all_whitespace(line))
         {
             // If the line is not a configuration line, it should be part of the map
             if (!is_configuration_line(line))
             {
                 free(line);
                 break;
             }
         }
         free(line);
     }
     if (!validate_configuration(game, parsed_elements))
         return (0);
     return (1);
 }

#include <stdbool.h>

bool flood_fill(char **grid, bool **visited, int x, int y, int rows, int cols) {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return true;

    if (visited[y][x] || grid[y][x] == '1')
        return false;

    visited[y][x] = true;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        if (flood_fill(grid, visited, x + dx[i], y + dy[i], rows, cols))
            return true;
    }

    return false;
}

int validate_map(t_game *game) {
    int player_count = 0;
    int player_x = -1, player_y = -1;

    for (int i = 0; i < game->map.rows; i++) {
        printf("Validating map row %d: '%s'\n", i + 1, game->map.grid[i]);
        for (size_t j = 0; j < ft_strlen(game->map.grid[i]); j++) {
            char c = game->map.grid[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                player_count++;
                player_x = j;
                player_y = i;
            }
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ') {
                fprintf(stderr, "Error: Invalid character '%c' in map at row %d, column %zu.\n", c, i + 1, j + 1);
                return 0;
            }
        }
    }
    printf("Player start position found at row %d, column %d.\n", player_y + 1, player_x + 1);

    if (player_count != 1) {
        fprintf(stderr, "Error: Map must have exactly one player start position. Found %d.\n", player_count);
        return 0;
    }

    bool **visited = ft_calloc(game->map.rows, sizeof(bool *));
    for (int i = 0; i < game->map.rows; i++) {
        visited[i] = ft_calloc(ft_strlen(game->map.grid[i]), sizeof(bool));
    }

    if (flood_fill(game->map.grid, visited, player_x, player_y, game->map.rows, ft_strlen(game->map.grid[0]))) {
        fprintf(stderr, "Error: Map is not enclosed by walls. Issue found starting at row %d, column %d.\n", player_y, player_x);
        for (int i = 0; i < game->map.rows; i++) {
            free(visited[i]);
        }
        free(visited);
        return 0;
    }

    for (int i = 0; i < game->map.rows; i++) {
        free(visited[i]);
    }
    free(visited);

    return 1;
}

int parse_map(t_game *game, int fd)
{
    char    *line;
    int     row;

    game->map.grid = ft_calloc(100, sizeof(char *));
    if (!game->map.grid)
    {
        ft_putendl_fd("Error: Memory allocation failed for map grid.", 2);
        return (0);
    }

    row = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Read map line: '%s'\n", line);
        char *trimmed_line = ft_strtrim(line, " \t\r\n");
        free(line);
        if (trimmed_line && ft_strlen(trimmed_line) > 0 && !is_all_whitespace(trimmed_line))
        {
            game->map.grid[row] = ft_strdup(trimmed_line);
            if (!game->map.grid[row])
            {
                ft_putendl_fd("Error: Memory allocation failed for map line.", 2);
                free(trimmed_line);
                for (int i = 0; i < row; i++)
                    free(game->map.grid[i]);
                free(game->map.grid);
                return (0);
            }
            printf("Stored map line %d: '%s'\n", row + 1, game->map.grid[row]);
            row++;
        }
        free(trimmed_line);
    }
    game->map.rows = row;
    game->map.cols = 0;

    if (!validate_map(game))
    {
        ft_putendl_fd("Error: Map validation failed.", 2);
        return (0);
    }
    return (1);
}

 void    cleanup_parser(t_game *game)
 {
     if (game->map.grid)
     {
         for (int i = 0; i < game->map.rows; i++)
         {
             free(game->map.grid[i]);
         }
         free(game->map.grid);
     }
     free(game->north_texture);
     free(game->south_texture);
     free(game->west_texture);
     free(game->east_texture);
 }

 int init_parser(t_game *game, const char *file_path)
 {
     int fd;

     // 초기화
     ft_memset(game, 0, sizeof(t_game));

     if (!check_file_extension(file_path))
     {
         ft_putendl_fd("Error: Configuration file must have a .cub extension.", 2);
         return (0);
     }
     fd = open(file_path, O_RDONLY);
     if (fd < 0)
     {
         perror("Error opening file");
         return (0);
     }
     if (!parse_configuration(game, fd))
     {
         close(fd);
         cleanup_parser(game);
         return (0);
     }
     close(fd);
     fd = open(file_path, O_RDONLY);
     if (fd < 0)
     {
         perror("Error reopening file");
         cleanup_parser(game);
         return (0);
     }
     if (!parse_map(game, fd))
     {
         close(fd);
         cleanup_parser(game);
         return (0);
     }
     close(fd);
     return (1);
 }
