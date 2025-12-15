#include "2048.h"

static void	draw_board(t_game *game);
static int	get_num_digits(int num);

int	render_game(t_game *game)
{
	int	key;
	int	game_over;

	game_over = 0;

	while (!game_over && !g_sigint_pressed)
	{
		clear();

		// Draw the game board
		draw_board(game);

		// Display score
		mvprintw(0, 0, "Score: %d", game->score);
		mvprintw(1, 0, "Use arrow keys to move, ESC to quit");

		refresh();

		// Get input
		key = getch();

		// Process arrow keys
		switch (key)
		{
			case KEY_UP:
				make_move(game, DIR_UP);
				break;
			case KEY_DOWN:
				make_move(game, DIR_DOWN);
				break;
			case KEY_LEFT:
				make_move(game, DIR_LEFT);
				break;
			case KEY_RIGHT:
				make_move(game, DIR_RIGHT);
				break;
			case ESC: // Exit game saving state and be able to continue from main menù
				return (0);
				break;
		}
	}
	
	return (0);
}

static void	draw_board(t_game *game)
{
	int	i;
	int	j;
	int	start_y;
	int	start_x;
	int	cell_width;
	int	cell_height;

	start_y = 3;
	start_x = 2;
	cell_width = 7;  // Width per cell (interior)
	cell_height = 2;  // Height per cell (interior)

	// Draw horizontal lines and cells
	for (i = 0; i <= game->size; i++)
	{
		// Draw horizontal line
		mvprintw(start_y + i * (cell_height + 1), start_x, "+");
		for (j = 0; j < game->size; j++)
		{
			for (int k = 0; k < cell_width; k++)
				addch('-');
			addch('+');
		}
		
		// Draw cell content (not after last row)
		if (i < game->size)
		{
			for (int row = 0; row < cell_height; row++)
			{
				mvprintw(start_y + i * (cell_height + 1) + row + 1, start_x, "|");
				for (j = 0; j < game->size; j++)
				{
					int value = game->board[i][j];
					if (row == cell_height / 2)
					{
						// Center row - show value
						if (value == 0)
						{
							for (int k = 0; k < cell_width; k++)
								addch(' ');
						}
						else
						{
							int digits = get_num_digits(value);
							int padding = (cell_width - digits) / 2;
							for (int k = 0; k < padding; k++)
								addch(' ');
							printw("%d", value);
							int remaining = cell_width - padding - digits;
							for (int k = 0; k < remaining; k++)
								addch(' ');
						}
					}
					else
					{
						// Empty row
						for (int k = 0; k < cell_width; k++)
							addch(' ');
					}
					addch('|');
				}
			}
		}
	}
}



static int	get_num_digits(int num)
{
	int	count;

	if (num == 0)
		return (1);

	count = 0;
	while (num > 0)
	{
		count++;
		num /= 10;
	}

	return (count);
}
