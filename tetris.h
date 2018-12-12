#include <SDL.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1
#define TETRAMINOBODY 4
#define TETRAMINO_GROUP_REF  tetramino_t tetramini[TETRAMINOBODY] //tetramino_group_t* tetramino_group;
#define TETRAMINO_REF tetramino_t *tetramino

typedef struct tetramino{
    int x;
    int y;
    int is_center;
}tetramino_t;

typedef struct tetris_map
{
    int width;
    int height;
    int *cell;
}tetris_map_t;

//MOVEMENT
int tetramino_move_right(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_right_check(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramino_move_left(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_left_check(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramino_move_down(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_down_check(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramino_all_move_down(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
int tetramino_all_move_right(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
int tetramino_all_move_left(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);

void tetramino_init(TETRAMINO_REF, tetris_map_t *tetris_map);

void tetris_map_init(tetris_map_t *tetris_map, int width, int height);

void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetramino_group_draw(TETRAMINO_GROUP_REF, SDL_Renderer *renderer, int size);

void tetris_check_fill_row(tetris_map_t *tetris_map);
void tetris_delete_fill_row(tetris_map_t *tetris_map, int row);

void tetramino_rotate(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map );
void tetramino_cube_init(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);

void tetramino_random_spawn(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
//string now only for debug , is useless , remove
void tetramino_spawn(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map, int x_0, int x_1, int x_2, int x_3,int y_0,int y_1,int y_2,int y_3,int index_center, const char* tetramino_name);
void tetramino_rot(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramini_to_map(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
int tetramino_check_rot(TETRAMINO_REF,tetris_map_t *tetris_map, int x, int y);
