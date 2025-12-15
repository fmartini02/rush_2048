#include "2048.h"

void	move_up(t_game *g, int j) {
	int		i = SIZE;
	int		num = 0;
	bool	repeat_flag = false;

	if (j >= SIZE)
		return;
	while (i > 0) {
		num = g->board[i - 1][j];
		if (num == g->board[i - 1][j]) {
			g->board[i - 1][j] = num + num;
			g->added = true;
			g->board[i][j] = 0;
			num = g->board[i - 1][j];
			repeat_flag = true;
			i = g->size;
		}
		else if (num != g->board[i - 1][j] && g->board[i - 1][j] != 0) {
			num = g->board[i - 1][j];
			repeat_flag = false;
		}
		else if (g->board[i - 1][j] == 0) {
			g->board[i - 1][j] = num;
			g->board[i][j] = 0;
			repeat_flag = true;
			i = g->size;
		}
		if (!repeat_flag)
			i++;
	}
	move_up(g, j + 1);
}

void	move_down(t_game *g, int j) {
	int		i = 0;
	int		num = 0;
	bool	repeat_flag = false;

	if (j >= SIZE)
		return;
	while (i < SIZE -1) {
		num = g->board[i][j];
		if (num == g->board[i + 1][j]) {
			g->board[i + 1][j] = num + num;
			g->board[i][j] = 0;
			g->added = true;
			num = g->board[i + 1][j];
			repeat_flag = true;
			i = g->size;
		}
		else if (num != g->board[i + 1][j] && g->board[i + 1][j] != 0) {
			num = g->board[i + 1][j];
			repeat_flag = false;
		}
		else if (g->board[i + 1][j] == 0) {
			g->board[i + 1][j] = num;
			g->board[i][j] = 0;
			repeat_flag = true;
			i = g->size;
		}
		if (!repeat_flag)
			i++;
	}
	move_down(g, j + 1);
}

void	move_left(t_game *g, int i) {
	int		j = SIZE;
	int		num = 0;
	bool	repeat_flag = false;

	if (i >= SIZE)
		return;
	while (j > 0) {
		num = g->board[i][j - 1];
		if (num == g->board[i][j - 1]) {
			g->board[i][j - 1] = num + num;
			g->board[i][j] = 0;
			g->added = true;
			num = g->board[i][j - 1];
			repeat_flag = true;
			j = g->size;
		}
		else if (num != g->board[i][j - 1] && g->board[i][j - 1] != 0) {
			num = g->board[i][j - 1];
			repeat_flag = false;
		}
		else if (g->board[i][j - 1] == 0) {
			g->board[i][j - 1] = num;
			g->board[i][j] = 0;
			repeat_flag = true;
			j = g->size;
		}
		if (!repeat_flag)
			j--;
	}
	move_left(g, i + 1);
}

void	move_right(t_game *g, int i) {
	int		j = 0;
	int		num = 0;
	bool	repeat_flag = false;

	if (i >= SIZE)
		return;
	while (j < SIZE -1) {
		num = g->board[i][j + 1];
		if (num == g->board[i][j + 1]) {
			g->board[i][j + 1] = num + num;
			g->board[i][j] = 0;
			g->added = true;
			num = g->board[i][j + 1];
			repeat_flag = true;
			i = 0;
		}
		else if (num != g->board[i][j + 1] && g->board[i][j + 1] != 0) {
			num = g->board[i][j + 1];
			repeat_flag = false;
		}
		else if (g->board[i][j + 1] == 0) {
			g->board[i][j + 1] = num;
			g->board[i][j] = 0;
			repeat_flag = true;
			j = 0;
		}
		if (!repeat_flag)
			j++;
	}
	move_right(g, i + 1);
}

void	set_bit_flag(int key, t_game *g) {
	uint8_t mask = 0;

	if (key == ESC) {
		g->esc = true;
		return;
	}
	mask |= (key == 'w' || key == 'W' || key == KEY_UP) * DIR_UP;
	mask |= (key == 's' ||  key == 'S' || key == KEY_DOWN) * DIR_DOWN;
	mask |= (key == 'a' ||  key == 'A' || key == KEY_LEFT) * DIR_LEFT;
	mask |= (key == 'd' ||  key == 'D' || key == KEY_RIGHT) * DIR_RIGHT;
	g->bit_flag |= mask;
	return;
}

void	process_input(t_game *g) {
	if (g->bit_flag & DIR_UP)
		move_up(g, 0);
	else if (g->bit_flag & DIR_DOWN)
		move_down(g, 0);
	else if (g->bit_flag & DIR_LEFT)
		move_left(g, 0);
	else if (g->bit_flag & DIR_RIGHT)
		move_right(g, 0);
	g->bit_flag = 0;
}

void	can_move(t_game *g)
{
	int i;
	int j;

	for (i = 0; i < g->size; i++)
	{
		for (j = 0; j < g->size; j++)
		{
			if (g->board[i][j] == 0){
				g->can_move = true;
				return;
			}
			if (i + 1 < g->size && g->board[i][j] == g->board[i + 1][j]){
				g->can_move = true;
				return;
			}
			if (j + 1 < g->size && g->board[i][j] == g->board[i][j + 1]){
				g->can_move = true;
				return;
			}
		}
	}
	g->can_move = false;
}

int main()
{
	t_game	g = (t_game){0};
	int		ch;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	g.size = SIZE;
	add_random_tile(&g);
	add_random_tile(&g);
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++)
			printw(" %d ", g.board[i][j]);
		printw("\n");
	}
	printw("\n");
	refresh();
	can_move(&g);
	while (g.can_move)
	{
		g.added = false;
		ch = getch();
		set_bit_flag(ch, &g);
		process_input(&g);
		can_move(&g);
		if (g.added && g.can_move)
			add_random_tile(&g);
		for(int i = 0; i < SIZE; i++) {
			for(int j = 0; j < SIZE; j++)
				printw(" %d ", g.board[i][j]);
			printw("\n");
		}
		printw("\n");
		refresh();
	}
}
