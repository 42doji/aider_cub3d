#ifndef STRUCT_H
#define STRUCT_H

// 맵 정보를 저장할 구조체
typedef struct s_map
{
    char **grid;
    int rows;
    int cols;
} t_map;

// 파싱 결과를 저장할 구조체
typedef struct s_game
{
    t_map map;
    // 추가적인 게임 관련 구조체 필드들
} t_game;

#endif // STRUCT_H
