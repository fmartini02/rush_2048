#include "2048.h"

t_game	*init_new_game(int size)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);

	game->size = size;
	game->score = 0;

	game->can_move = true;
	game->added = false;

	game->board = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
	{
		game->board[i] = malloc(sizeof(int) * size);
		// Initialize all cells to 0
		for (int j = 0; j < size; j++)
			game->board[i][j] = 0;
	}

	// the game starts with two tiles
	add_random_tile(game);
	add_random_tile(game);

	return (game);
}

void	free_game(t_game *game)
{
	if (!game)
		return;

	for (int i = 0; i < game->size; i++)
		free(game->board[i]);

	free(game->board);
	free(game);
}

void add_random_tile(t_game *game)
{
	int empty_cells[game->size * game->size][2];
	int empty_count = 0;
	int i, j;

	for (i = 0; i < game->size; i++)
	{
		for (j = 0; j < game->size; j++)
		{
			if (game->board[i][j] == 0)
			{
				empty_cells[empty_count][0] = i;
				empty_cells[empty_count][1] = j;
				empty_count++;
			}
		}
	}

	if (empty_count == 0)
		return;

	int rand_index = rand() % empty_count;
	int row = empty_cells[rand_index][0];
	int col = empty_cells[rand_index][1];

	game->board[row][col] = (rand() % 10 == 0) ? 4 : 2;
	game->added = 1;
}

