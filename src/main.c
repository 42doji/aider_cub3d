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

#include <dirent.h>
#include "../include/cub3d.h"

int main(void)
{
    DIR *dir;
    struct dirent *entry;
    char filepath[512];
    char *line;
    int fd;

    dir = opendir("src/test");
    if (dir == NULL)
    {
        perror("opendir 실패?");
        return (1);
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".txt") != NULL)
        {
            snprintf(filepath, sizeof(filepath), "src/test/%s", entry->d_name);
            printf("Testing file: %s\n", filepath);
            fd = open(filepath, O_RDONLY);
            if (fd == -1)
            {
                perror("파일 열기 실패");
                continue;
            }
            while ((line = get_next_line(fd)) != NULL)
            {
                printf("%s", line);
                free(line);
            }
            close(fd);
            printf("\n--- %s 종료 ---\n\n", entry->d_name);
        }
    }

    closedir(dir);
    return (0);
}
