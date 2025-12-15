#include "2048.h"

// // void init_game(t_game *g);
// void move_left(t_game *g);
// void move_right(t_game *g);
// void move_up(t_game *g);
// void move_down(t_game *g);
// void add_random_num(t_game *g);
// int can_move(t_game *g);

// void	move_up(t_game *g) {
// 	int	i = g->size - 1, j = 0;
// 	int	num = 0;

// 	// while (i)
// }

// void	move_down(t_game *g) {

// }

// void	move_left(t_game *g) {

// }

// void	move_right(t_game *g) {

// }
// void	set_bit_flag(int key, t_game *g) {
// 	uint8_t mask = 0;

// 	if (key = ESC) {
// 		// g->esc = true;
// 		return;
// 	}
// 	mask |= (key == 'w' || key == 'W' || key == KEY_UP) * DIR_UP;
// 	mask |= (key == 's' ||  key == 'S' || key == KEY_DOWN) * DIR_DOWN;
// 	mask |= (key == 's' ||  key == 'S' || key == KEY_LEFT) * DIR_LEFT;
// 	mask |= (key == 's' ||  key == 'S' || key == KEY_RIGHT) * DIR_RIGHT;
// 	g->bit_flag |= mask;
// 	return;
// }

// void process_input(t_game *g)
// {
// 	if (g->bit_flag & KEY_UP)
// 		move_up(g);
// 	else if (g->bit_flag & KEY_DOWN)
// 		move_down(g);
// 	else if (g->bit_flag & KEY_LEFT)
// 		move_left(g);
// 	else if (g->bit_flag & KEY_RIGHT)
// 		move_right(g);
// 	g->bit_flag = 0;
// }

// return 1 on win, 0 otherwise, -1 on loss
int	make_move(t_game *game, int direction)
{
	(void)game;
	(void)direction;

	return (0);
}

// TO DO remove this function later
void	test_move()
{
	// t_game	*g = init_new_game(4);
	// int		ch;

	// initscr();
	// cbreak();
	// noecho();
	// keypad(stdscr, TRUE);
	// while (can_move)
	// {
	// 	ch = getch();
	// 	set_bit_flag(ch, &g);
	// 	process_movement(&g);
	// }
}