#ifndef PARSER_H
#define PARSER_H

#include "struct.h"

// 파서 초기화 함수
int init_parser(t_game *game, const char *file_path);

// 맵을 파싱하는 함수
int parse_map(t_game *game, const char *line);

#endif // PARSER_H
