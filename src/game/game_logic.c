#include "2048.h"

void line_up(int *arr, int size)
{
	int write = 0;

	for (int read = 0; read < size; read++)
	{
		if (arr[read] != 0)
		{
			arr[write++] = arr[read];
		}
	}
	while (write < size)
		arr[write++] = 0;
}

void merge(int *arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] != 0 && arr[i] == arr[i + 1])
		{
			arr[i] *= 2;
			arr[i + 1] = 0;
			i++; // skip next tile (IMPORTANT)
		}
	}
	line_up(arr, size);
}

int move_up(t_game *g)
{
	int *arr = ft_malloc(sizeof(int) * g->size, 0);
	if (!arr)
		return -1;

	for (int j = 0; j < g->size; j++)
	{
		for (int i = 0; i < g->size; i++)
			arr[i] = g->board[i][j];

		line_up(arr, g->size);
		merge(arr, g->size);

		for (int i = 0; i < g->size; i++)
			g->board[i][j] = arr[i];
	}
	free(arr);
	return 0;
}


int move_down(t_game *g)
{
	int *arr = ft_malloc(sizeof(int) * g->size, 0);
	if (!arr)
		return -1;

	for (int j = 0; j < g->size; j++)
	{
		int idx = 0;

		for (int i = g->size - 1; i >= 0; i--)
			arr[idx++] = g->board[i][j];

		line_up(arr, g->size);
		merge(arr, g->size);

		idx = 0;
		for (int i = g->size - 1; i >= 0; i--)
			g->board[i][j] = arr[idx++];
	}
	free(arr);
	return 0;
}

int move_left(t_game *g)
{
	int *arr = ft_malloc(sizeof(int) * g->size, 0);
	if (!arr)
		return -1;

	for (int i = 0; i < g->size; i++)
	{
		for (int j = 0; j < g->size; j++)
			arr[j] = g->board[i][j];

		line_up(arr, g->size);
		merge(arr, g->size);

		for (int j = 0; j < g->size; j++)
			g->board[i][j] = arr[j];
	}
	free(arr);
	return 0;
}


int move_right(t_game *g)
{
	int *arr = ft_malloc(sizeof(int) * g->size, 0);
	if (!arr)
		return -1;

	for (int i = 0; i < g->size; i++)
	{
		int idx = 0;

		for (int j = g->size - 1; j >= 0; j--)
			arr[idx++] = g->board[i][j];

		line_up(arr, g->size);
		merge(arr, g->size);

		idx = 0;
		for (int j = g->size - 1; j >= 0; j--)
			g->board[i][j] = arr[idx++];
	}
	free(arr);
	return 0;
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
		move_up(g);
	else if (dir == DIR_DOWN)
		move_down(g);
	else if (dir == DIR_LEFT)
		move_left(g);
	else if (dir == DIR_RIGHT)
		move_right(g);
	if (g->added && g->can_move)
		add_random_tile(g);
	return (0);
}
