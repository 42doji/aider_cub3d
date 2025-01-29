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
        return (0);

    const char *extension = ".cub";
    size_t len = ft_strlen(filename);
    size_t ext_len = ft_strlen(extension);

    if (len < ext_len)
        return (0);

    return (ft_strncmp(&filename[len - ext_len], extension, ext_len) == 0);
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
         if (ft_strlen(line) == 0 || is_all_whitespace(line))
         {
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
             free(line);
             break;
         }
         free(line);
     }
     if (!validate_configuration(game, parsed_elements))
         return (0);
     return (1);
 }

int validate_map(t_game *game)
{
    int player_count = 0;

    for (int i = 0; i < game->map.rows; i++)
    {
        for (size_t j = 0; j < ft_strlen(game->map.grid[i]); j++)
        {
            char c = game->map.grid[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
            if ((i == 0 || i == game->map.rows - 1 || j == 0 || j == ft_strlen(game->map.grid[i]) - 1) && c != '1')
            {
                ft_putendl_fd("Error: Map is not enclosed by walls.", 2);
                return (0);
            }
            if (c == '0' && (i == 0 || i == game->map.rows - 1 || j == 0 || j == ft_strlen(game->map.grid[i]) - 1))
            {
                ft_putendl_fd("Error: Map is not enclosed by walls.", 2);
                return (0);
            }
        }
    }

    if (player_count != 1)
    {
        ft_putendl_fd("Error: Map must have exactly one player start position.", 2);
        return (0);
    }

    return (1);
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
        if (ft_strlen(line) > 0 && !is_all_whitespace(line))
        {
            game->map.grid[row] = ft_strdup(line);
            if (!game->map.grid[row])
            {
                ft_putendl_fd("Error: Memory allocation failed for map line.", 2);
                free(line);
                return (0);
            }
            row++;
        }
        free(line);
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
     if (!parse_map(game, fd))
     {
         close(fd);
         cleanup_parser(game);
         return (0);
     }
     close(fd);
     return (1);
 }
