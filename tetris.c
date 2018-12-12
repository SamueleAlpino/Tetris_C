#include "tetris.h"

void tetramino_init(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

void tetramino_spawn(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map, int x_0, int x_1, int x_2, int x_3, int y_0, int y_1, int y_2, int y_3, int index_center, const char *tetramino_name)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen + x_0;
    tetramini[0].y = y_0;

    tetramini[1].x = half_screen + x_1;
    tetramini[1].y = y_1;

    tetramini[2].x = half_screen + x_2;
    tetramini[2].y = y_2;

    tetramini[3].x = half_screen + x_3;
    tetramini[3].y = y_3;

    int i;

    if (index_center != -1)
        tetramini[index_center].is_center = 1;

    for (i = 0; i < TETRAMINOBODY; i++)
    {
        if (i != index_center)
            tetramini[i].is_center = 0;
    }
}

void tetramino_random_spawn(tetramino_t tetramino[4], tetris_map_t *tetris_map)
{
    //  int random = 1 + (6 * rand() / (RAND_MAX + 1));
    int random = 0 + (7 * rand() / (RAND_MAX + 1));
    printf("%d \n", random);
    switch (random)
    {
    case 0:
        tetramino_spawn(tetramino, tetris_map, -1, 0, -1, 0, 0, 0, 1, 1, -1, "Cube");
        break;
    case 1:
        tetramino_spawn(tetramino, tetris_map, -1, -2, 0, -2, 1, 1, 1, 0, 0, "J");
        break;
    case 2:
        tetramino_spawn(tetramino, tetris_map, -1, 0, -1, -2, 0, 0, 1, 1, 2, "S");
        break;
    case 3:
        tetramino_spawn(tetramino, tetris_map, -1, -2, -1, 0, 0, 0, 1, 1, 0, "Z");
        break;
    case 4:
        tetramino_spawn(tetramino, tetris_map, -1, -2, 0, 0, 1, 1, 1, 0, 0, "L");
        break;
    case 5:
        tetramino_spawn(tetramino, tetris_map, -1, -2, 0, -1, 1, 1, 1, 0, 0, "T");
        break;
    case 6:
        tetramino_spawn(tetramino, tetris_map, -1, -2, 0, 1, 1, 1, 1, 1, 1, "L");
        break;
    }
}
int tetramino_all_move_down(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map)
{
    for (int i = 0; i < TETRAMINOBODY; i++)
    {
        if (tetramino_move_down_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
        {
            tetramini_to_map(tetramini, tetris_map);
            return TETRAMINO_DEAD;
        }
    }

    for (int i = 0; i < TETRAMINOBODY; i++)
        tetramino_move_down(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_all_move_right(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map)
{
    //check if all pieces can move in next position
    for (int i = 0; i < TETRAMINOBODY; i++)
    {
        if (tetramino_move_right_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
            return TETRAMINO_DEAD;
    }

    for (int i = 0; i < TETRAMINOBODY; i++)
        tetramino_move_right(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_all_move_left(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map)
{
    //check if all pieces can move in next position
    for (int i = 0; i < TETRAMINOBODY; i++)
    {
        if (tetramino_move_left_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
            return TETRAMINO_DEAD;
    }

    for (int i = 0; i < TETRAMINOBODY; i++)
        tetramino_move_left(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_move_down_check(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= tetris_map->height)
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    if (tetris_map->cell[next_index] == 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_down(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetris_map->cell[next_index] == 0)
    {
        tetramino->y += 1;
    }
    else
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    tetris_check_fill_row(tetris_map);

    return TETRAMINO_OK;
}

int tetramini_to_map(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map)
{
    int current_index;
    int next_index;

    for (int i = 0; i < TETRAMINOBODY; i++)
    {
        current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;
        next_index = tetris_map->width * (tetramini[i].y + 1) + tetramini[i].x;
        tetris_map->cell[current_index] = 1;
    }

    return TETRAMINO_DEAD;
}

int tetramino_move_right_check(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    if (tetramino->x >= tetris_map->width - 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_right(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    int right_index = tetris_map->width * tetramino->y + (tetramino->x + 1);
    if (!tetris_map->cell[right_index])
    {
        tetramino->x++;
    }

    return TETRAMINO_OK;
}

int tetramino_move_left_check(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    if (tetramino->x <= 0)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_left(TETRAMINO_REF, tetris_map_t *tetris_map)
{
    tetramino->x--;
    return TETRAMINO_OK;
}

void tetris_map_init(tetris_map_t *tetris_map, int width, int height)
{
    int size = sizeof(int) * width * height;

    tetris_map->cell = malloc(size);
    memset(tetris_map->cell, 0, size);
    tetris_map->width = width;
    tetris_map->height = height;
}

void tetris_check_fill_row(tetris_map_t *tetris_map)
{
    int row;
    int column;

    // For each row of the Tetris map
    for (row = 0; row < tetris_map->height; row++)
    {
        int tetramini = 0;
        for (column = 0; column < tetris_map->width; column++)
        {
            // We count how many tetramini are in the row
            if (tetris_map->cell[(row * tetris_map->width) + column] == 1)
                tetramini += 1;
        }

        if (tetramini >= tetris_map->width)
            tetris_delete_fill_row(tetris_map, row);
    }
}

void tetris_delete_fill_row(tetris_map_t *tetris_map, int row)
{
    int row_index = tetris_map->width * row;

    int i;
    for (i = (row_index + tetris_map->width); i > tetris_map->width; i--)
        tetris_map->cell[i] = tetris_map->cell[i - tetris_map->width];
}

void tetramino_rot(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map)
{
    int i;
    int current_center;
    for (i = 0; i < TETRAMINOBODY; i++)
    {
        if (tetramini[i].is_center == 1)
            current_center = i;
    }

    if (tetramini[current_center].is_center == 1)
    {
        for (i = 0; i < TETRAMINOBODY; i++)
        {
            if (tetramini[i].is_center == 0)
            {
                int x = SDL_abs(tetramini[current_center].x - tetramini[i].x);
                int y = SDL_abs(tetramini[current_center].y - tetramini[i].y);

                int n = x + y;

                if (tetramini[current_center].x < tetramini[i].x &&
                    tetramini[current_center].y > tetramini[i].y && n == 2)
                {
                    if (tetramino_check_rot(&tetramini[i], tetris_map, 0, n) == 0)
                    {
                        tetramini[i].y += n;
                    }
                }
                else if (tetramini[current_center].x < tetramini[i].x &
                             tetramini[current_center].y < tetramini[i].y &&
                         n == 2)
                {
                    if (tetramino_check_rot(&tetramini[i], tetris_map, -n, 0) == 0)
                    {
                        tetramini[i].x -= n;
                    }
                }
                else if (tetramini[current_center].x > tetramini[i].x &
                             tetramini[current_center].y < tetramini[i].y &&
                         n == 2)
                {
                    if (tetramino_check_rot(&tetramini[i], tetris_map, 0, -n) == 0)
                    {
                        tetramini[i].y -= n;
                    }
                }
                else if (tetramini[current_center].x > tetramini[i].x &
                             tetramini[current_center].y > tetramini[i].y &&
                         n == 2)
                {
                    if (tetramino_check_rot(&tetramini[i], tetris_map, n, 0) == 0)
                    {
                        tetramini[i].x += n;
                    }
                }
                else
                {
                    if (tetramini[current_center].x < tetramini[i].x &&
                        tetramini[current_center].y == tetramini[i].y)
                    {
                        if (tetramino_check_rot(&tetramini[i], tetris_map, -n, n) == 0)
                        {
                            tetramini[i].x -= n;
                            tetramini[i].y += n;
                        }
                    }
                    else if (tetramini[current_center].x == tetramini[i].x &
                             tetramini[current_center].y < tetramini[i].y)
                    {
                        if (tetramino_check_rot(&tetramini[i], tetris_map, -n, -n) == 0)
                        {
                            tetramini[i].x -= n;
                            tetramini[i].y -= n;
                        }
                    }
                    else if (tetramini[current_center].x > tetramini[i].x &
                             tetramini[current_center].y == tetramini[i].y)
                    {
                        if (tetramino_check_rot(&tetramini[i], tetris_map, n, -n) == 0)
                        {
                            tetramini[i].x += n;
                            tetramini[i].y -= n;
                        }
                    }
                    else if (tetramini[current_center].x == tetramini[i].x &
                             tetramini[current_center].y > tetramini[i].y)
                    {
                        if (tetramino_check_rot(&tetramini[i], tetris_map, n, n) == 0)
                        {
                            tetramini[i].x += n;
                            tetramini[i].y += n;
                        }
                    }
                }
            }
        }
    }
}
//Fix index
int tetramino_check_rot(TETRAMINO_REF, tetris_map_t *tetris_map, int x, int y)
{
    int temp_x = tetramino->x + x;
    int temp_y = tetramino->y + y;

    int current_index = tetris_map->width * temp_x + temp_y;

    if (tetris_map->cell[current_index] == 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}
