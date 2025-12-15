#include "2048.h"

t_game	*init_new_game(int size)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);

	game->size = size;
	game->score = 0;
	game->bit_flag = 0;

	game->board = malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
		game->board[i] = malloc(sizeof(int) * size);

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