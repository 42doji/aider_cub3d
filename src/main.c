/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c.backup                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:21:15 by doji              #+#    #+#             */
/*   Updated: 2025/01/28 23:21:20 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int main(int argc, char *argv[])
{
    t_game game;

    if (argc != 2)
    {
        ft_putendl_fd("Usage: ./cub3d <map.cub>", 2);
        return (1);
    }

    if (!init_parser(&game, argv[1]))
    {
        ft_putendl_fd("Parsing failed.", 2);
        return (1);
    }

    // 파싱 결과 출력 (디버깅용)
    printf("North Texture: %s\n", game.north_texture);
    printf("South Texture: %s\n", game.south_texture);
    printf("West Texture: %s\n", game.west_texture);
    printf("East Texture: %s\n", game.east_texture);
    printf("Floor Color: %d\n", game.floor_color);
    printf("Ceiling Color: %d\n", game.ceiling_color);
    printf("Map Rows: %d\n", game.map.rows);

    // 맵 출력
    for (int i = 0; i < game.map.rows; i++)
    {
        printf("%s\n", game.map.grid[i]);
    }

    cleanup_parser(&game);
    return (0);
}


//
//
//
//int main(int argc, char *argv[])
//{
//    t_game game;
//
//    if (argc != 2)
//    {
//        ft_putendl_fd("Usage: ./cub3D map.cub", 2);
//        return (EXIT_FAILURE);
//    }
//
//    if (!init_parser(&game, argv[1]))
//        return (EXIT_FAILURE);
//
//    // 이후 게임 초기화 및 실행 로직
//    return (EXIT_SUCCESS);
//}
