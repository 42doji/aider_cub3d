/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:45:15 by doji              #+#    #+#             */
/*   Updated: 2025/01/29 00:45:35 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_map
{
    char **grid;
    int rows;
    int cols;
}	t_map;

typedef struct s_game
{
    t_map map;
    double player_x;   // 플레이어의 X 좌표
    double player_y;   // 플레이어의 Y 좌표
    double dir_x;      // 플레이어의 방향 벡터 X
    double dir_y;      // 플레이어의 방향 벡터 Y

    // 텍스처 경로
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;

    // 색상 정보
    int floor_color;
    int ceiling_color;
} t_game;
#endif 
