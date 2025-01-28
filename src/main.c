/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_gnl.c                                             :+:      :+:    :+:   */
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
    printf("%d %s\n", argc, argv[1]);

    // test get_next_line
    int fd = open("test.txt", O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (EXIT_SUCCESS);
}
