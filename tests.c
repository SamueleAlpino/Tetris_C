#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRAMINO_SETUP(width, height)           \
	tetramino_t tetramino;                       \
	tetris_map_t tetris_map;                     \
	tetris_map_init(&tetris_map, width, height); \
	tetramino_init(&tetramino, &tetris_map)

TEST(tetramino_init)
{
	TETRAMINO_SETUP(1, 1);

	ASSERT_THAT(tetramino.y == -1);
}

TEST(tetramino_move_down)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 0);
}

TEST(tetramino_move_right_blocked)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	
	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_right)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_right_multiple)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_right(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_left_blocked)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_left(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_left(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left_multiple)
{
	TETRAMINO_SETUP(3, 1);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_right(&tetramino, &tetris_map);
	tetramino_move_left(&tetramino, &tetris_map);
	tetramino_move_left(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_down_wrong_value)
{
	TETRAMINO_SETUP(1, 1);
	tetramino.y = 100;
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 100);
}

TEST(tetramino_busy_cell)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_t tetramino2;
	tetramino_init(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	ASSERT_THAT(tetramino2.y == -1);
}

TEST(tetramino_fill_two_blocks)
{
	TETRAMINO_SETUP(2, 2);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);

	ASSERT_THAT(tetramino.y == 1);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	SDL_Log("%d", tetramino2.y);

	ASSERT_THAT(tetramino2.y == 0);
}

TEST(tetramino_dead)
{
	TETRAMINO_SETUP(1, 2);

	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_OK);
	ASSERT_THAT(tetramino_move_down(&tetramino, &tetris_map) == TETRAMINO_DEAD);
}

TEST(test_spawn)
{
	tetris_map_t map;
	tetris_map_init(&map, 10, 20);

	tetramino_t tetramino_group[TETRAMINOBODY];
	tetramino_spawn(tetramino_group, &map, -1, -2, 0, 1, 1, 1, 1, 1, 1, "L");
	ASSERT_THAT(tetramino_group[0].x == map.width/2  - 1);
	ASSERT_THAT(tetramino_group[1].x == map.width/2  - 2);
	ASSERT_THAT(tetramino_group[2].x == map.width/2);
	ASSERT_THAT(tetramino_group[3].x == map.width/2 + 1);

	ASSERT_THAT(tetramino_group[0].y == 1);
	ASSERT_THAT(tetramino_group[1].y == 1);
	ASSERT_THAT(tetramino_group[2].y == 1);
	ASSERT_THAT(tetramino_group[3].y == 1);

	ASSERT_THAT(tetramino_group[1].is_center == 1);
}
// Why is this test passing?
TEST(check_row_filled_2x2)
{
	TETRAMINO_SETUP(2, 2);
	tetramino_move_left(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);
	tetramino_move_down(&tetramino, &tetris_map);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, &tetris_map);
	tetramino_move_right(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);
	tetramino_move_down(&tetramino2, &tetris_map);

	ASSERT_THAT(tetris_map.cell[2] == 0);
	ASSERT_THAT(tetris_map.cell[3] == 0);
}

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1, 1);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}
int main(int argc, char **argv)
{
	RUN_TEST(tetramino_map_init);
	RUN_TEST(test_spawn);

	PRINT_TEST_RESULTS();
	return 0;
}
