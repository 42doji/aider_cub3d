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
        ft_putendl_fd("Usage: ./cub3D map.cub", 2);
        return (EXIT_FAILURE);
    }

    if (!init_parser(&game, argv[1]))
        return (EXIT_FAILURE);

    // 이후 게임 초기화 및 실행 로직
    return (EXIT_SUCCESS);
}
