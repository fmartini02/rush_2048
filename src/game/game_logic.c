#include "2048.h"

void	line_up(int **arr, int size) {
	int		i = 0, j = 1;
	bool	end = false;

	while (!end) {
		end = true;
		while (j < size) {
			if (*arr[i] == 0 && *arr[j] != 0) {
				*arr[i] = *arr[j];
				*arr[j] = 0;
				end = false;
			}
			i++;
			j++;
		}
		i = 0;
		j = 1;
	}
}

void	merge(int **arr, int size) {
	int		i = 0, j = 1;

	while (j < size){
		if (*arr[i] == *arr[j]) {
			*arr[i] += *arr[j];
			*arr[j] = 0;
			line_up(arr, size);
		}
		i++;
		j++;
	}
}

int	move_up(t_game *g, int j) {
	int i = 0;
	int	*arr;
	int	**dummy_board;

	arr = ft_malloc(sizeof(int) * g->size, 0);
	if (!arr)
		return -1;
	dummy_board = g->board;
	while (j < g->size) {
		while (i < g->size) {
			arr[i] = dummy_board[i][j];
			i++;
		}
		line_up(&arr, g->size);
		merge(&arr, g->size);
		i = 0;
		while (i < g->size) {
			dummy_board[i][j] = arr[i];
			i++;
		}
		i=0;
		j++;
	}
	g->board = dummy_board;
	return 0;
}

int	move_down(t_game *g, int j) {
	int i = 0;
	int	*arr;
	int	**dummy_board;

	arr = ft_malloc(sizeof(int) * g->size, 0);
	if (!arr)
		return -1;
	dummy_board = g->board;
	while (j < g->size) {
		for (int k = g->size; k > 0; k--) {
			arr[i] = dummy_board[k][j];
			i++;
		}
		line_up(&arr, g->size);
		merge(&arr, g->size);
		for (int k = g->size; k > 0; k--) {
			dummy_board[k][j] = arr[i];
			i++;
		}
		i = 0;
		j++;
	}
	g->board = dummy_board;
	return 0;
}

void	move_left(t_game *g, int i) {
	int		j = g->size - 1;
	int		num = 0;
	bool	repeat_flag = false;

	if (i >= g->size)
		return;
	while (j > 0) {
		num = g->board[i][j - 1];
		if (num == g->board[i][j - 1]) {
			g->board[i][j - 1] = num + num;
			g->board[i][j] = 0;
			g->added = true;
			num = g->board[i][j - 1];
			repeat_flag = true;
			j = 0;
		}
		else if (num != g->board[i][j - 1] && g->board[i][j - 1] != 0) {
			num = g->board[i][j - 1];
			repeat_flag = false;
		}
		else if (g->board[i][j - 1] == 0) {
			g->board[i][j - 1] = num;
			g->board[i][j] = 0;
			repeat_flag = true;
			j = 0;
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

	if (i >= g->size)
		return;
	while (j < g->size -1) {
		num = g->board[i][j + 1];
		if (num == g->board[i][j + 1]) {
			g->board[i][j + 1] = num + num;
			g->board[i][j] = 0;
			g->added = true;
			num = g->board[i][j + 1];
			repeat_flag = true;
			j = g->size - 1;
		}
		else if (num != g->board[i][j + 1] && g->board[i][j + 1] != 0) {
			num = g->board[i][j + 1];
			repeat_flag = false;
		}
		else if (g->board[i][j + 1] == 0) {
			g->board[i][j + 1] = num;
			g->board[i][j] = 0;
			repeat_flag = true;
			j = g->size - 1;
		}
		if (!repeat_flag)
			j++;
	}
	move_right(g, i + 1);
}

// void	set_bit_flag(int key, t_game *g) {
// 	uint8_t mask = 0;

// 	if (key == ESC) {
// 		g->esc = true;
// 		return;
// 	}
// 	mask |= (key == 'w' || key == 'W' || key == KEY_UP) * DIR_UP;
// 	mask |= (key == 's' ||  key == 'S' || key == KEY_DOWN) * DIR_DOWN;
// 	mask |= (key == 'a' ||  key == 'A' || key == KEY_LEFT) * DIR_LEFT;
// 	mask |= (key == 'd' ||  key == 'D' || key == KEY_RIGHT) * DIR_RIGHT;
// 	g->bit_flag |= mask;
// 	return;
// }

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

int make_move(t_game *g, int dir)
{
	if (dir == DIR_UP)
		move_up(g, 0);
	else if (dir == DIR_DOWN)
		move_down(g, 0);
	else if (dir == DIR_LEFT)
		move_left(g, 0);
	else if (dir == DIR_RIGHT)
		move_right(g, 0);
	if (g->added && g->can_move)
		add_random_tile(g);
	return (0);
}
