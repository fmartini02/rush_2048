#include "2048.h"

t_game	*init_new_game(int size)
{
	t_game	*game;

	game = (t_game *)ft_malloc(sizeof(t_game), 0);
	if (!game)
		return (NULL);

	game->size = size;
	game->score = 0;

	game->can_move = true;
	game->added = false;

	game->win_displayed = false;

	game->win_condition = WIN_VALUE;

	game->board = ft_malloc(sizeof(int *) * size, 0);
	for (int i = 0; i < size; i++)
	{
		game->board[i] = ft_malloc(sizeof(int) * size, 0);
		// Initialize all cells to 0
		for (int j = 0; j < size; j++)
			game->board[i][j] = 0;
	}

	// the game starts with two tiles
	add_random_tile(game);
	add_random_tile(game);

	return (game);
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

int	load_best_score()
{
	int		fd;
	int		best_score = 0;
	char	buffer[32];
	ssize_t	bytes_read;

	fd = open(".2048_best_score", O_RDONLY);
	if (fd != -1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			best_score = atoi(buffer);
		}
		close(fd);
	}
	return (best_score);
}

void	save_best_score(int score)
{
	int		fd;
	int		current_best;
	char	buffer[32];
	int		len;

	current_best = load_best_score();
	if (score > current_best)
	{
		fd = open(".2048_best_score", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
		{
			buffer = ft_itoa(score);
			len = ft_strlen(buffer);
			write(fd, buffer, len);
			close(fd);
		}
	}
}
