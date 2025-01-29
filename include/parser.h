/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:44:56 by doji              #+#    #+#             */
/*   Updated: 2025/01/29 00:45:13 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

int		init_parser(t_game *game, const char *file_path);
int		check_file_extension(const char *filename);
int		parse_configuration(t_game *game, int fd);
int		parse_map(t_game *game, int fd);
int		handle_configuration_line(t_game *game, char *line);
int		is_configuration_line(char *line);
int		validate_configuration(t_game *game, int parsed_elements);
int		validate_map(t_game *game);
void    cleanup_parser(t_game *game);
#endif
