/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:21:15 by doji              #+#    #+#             */
/*   Updated: 2025/01/28 23:21:20 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (init_parser(&game, argv[1]) == -1) {
        fprintf(stderr, "Error parsing the map file.\n");
        return EXIT_FAILURE;
    }

    printf("Map loaded successfully.\n");
    return EXIT_SUCCESS;
}
