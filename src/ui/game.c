#include "2048.h"

static int	handle_move(t_game *game, int direction);
static void	draw_board(t_game *game);
static int	get_num_digits(int num);
static int	get_color_pair(int value);

// Return 0 = ESC pressed, 1 = game over (win or loss)
int	render_game(t_game *game)
{
	int	key;
	int	game_over;
	int	needs_redraw;
	int	best_score;

	game_over = 0;
	needs_redraw = 1;
	best_score = load_best_score();

	while (!game_over && !g_sigint_pressed)
	{
		if (needs_redraw)
		{
			erase();

			// Draw the game board
			draw_board(game);

			// Update best score if current score is higher
			if (game->score > best_score)
				best_score = game->score;

			// Display score and best score
			mvprintw(0, 0, "Score: %d", game->score);
			mvprintw(0, 20, "Best: %d", best_score);
			mvprintw(1, 0, "Use arrow keys to move, ESC to quit");

			refresh();
			needs_redraw = 0;
		}

		// Get input
		key = getch();

		if (key == ERR)
			continue;

		// Ignore mouse events (including scroll wheel)
		if (key == KEY_MOUSE)
			continue;

		// Process arrow keys
		switch (key)
		{
			case KEY_UP:
				if (handle_move(game, DIR_UP) == -1)
					game_over = 1;
				else
					needs_redraw = 1;
				break;
			case KEY_DOWN:
				if (handle_move(game, DIR_DOWN) == -1)
					game_over = 1;
				else
					needs_redraw = 1;
				break;
			case KEY_LEFT:
				if (handle_move(game, DIR_LEFT) == -1)
					game_over = 1;
				else
					needs_redraw = 1;
				break;
			case KEY_RIGHT:
				if (handle_move(game, DIR_RIGHT) == -1)
					game_over = 1;
				else
					needs_redraw = 1;
				break;
			case KEY_RESIZE:
				// Handle terminal resize
				needs_redraw = 1;
				break;
			case ESC: // Exit game saving state and be able to continue from main menù
				save_best_score(game->score);
				clear();
				return (0);
				break;
		}
	}

	if (game_over)
	{
		save_best_score(game->score);
		return (1);
	}

	return (0);
}

// Return 1 if redraw is needed, -1 for game over (win or loss)
static int	handle_move(t_game *game, int direction)
{
	int	move_result = make_move(game, direction);

	// victory
	if (move_result == 1)
	{
		if (game->win_displayed == false)
		{
			game->win_displayed = true;

			clear();
			mvprintw(2 + game->size * 7 / 2, 2, "You Win!");
			mvprintw(2 + game->size * 7 / 2 + 2, 2, "Press 'C' to continue playing or ESC to exit.");
			refresh();

			cbreak();  // Disable halfdelay, enable blocking mode
			int choice;
			while (1)
			{
				choice = getch();
				if (choice == 'c' || choice == 'C')
				{
					halfdelay(1);  // Restore halfdelay mode
					return (1);  // Continue playing, needs redraw
				}
				else if (choice == ESC)
				{
					halfdelay(1);  // Restore halfdelay mode
					return (-1);  // Exit game
				}
			}
		}

		return (1);
	}

	// loss
	if (move_result == -1)
	{
		clear();
		mvprintw(2 + game->size * 7 / 2, 2, "Game Over! Press any key to exit.");
		refresh();
		cbreak();  // Disable halfdelay, enable blocking mode
		getch();
		halfdelay(1);  // Restore halfdelay mode
		return (-1);
	}

	// valid move, continue playing and need redraw
	return (1);
}

static void	draw_board(t_game *game)
{
	int	i, j;
	int	start_y, start_x;
	int	cell_width, cell_height;
	int max_y, max_x;

	// Get terminal size
	getmaxyx(stdscr, max_y, max_x);

	// Calculate cell dimensions based on terminal size
	cell_width = (max_x - 4) / game->size - 2;
	cell_height = (max_y - 6) / game->size - 1;

	// Minimum size constraints
	if (cell_width < 12)
		cell_width = 12;
	if (cell_height < 6)
		cell_height = 6;

	start_y = 3;
	start_x = 2;

	// Draw cells with spacing
	for (i = 0; i < game->size; i++)
	{
		for (j = 0; j < game->size; j++)
		{
			int value = game->board[i][j];
			int color = get_color_pair(value);
			int cell_y = start_y + i * (cell_height + 1);
			int cell_x = start_x + j * (cell_width + 2);

			// Draw cell with rounded corners effect
			for (int row = 0; row < cell_height; row++)
			{
				move(cell_y + row, cell_x);
				
				if (has_colors())
					attron(COLOR_PAIR(color));

				// Top and bottom rows - slightly rounded
				if (row == 0 || row == cell_height - 1)
				{
					addch(' ');
					for (int k = 1; k < cell_width - 1; k++)
						addch(' ');
					addch(' ');
				}
				else if (value == 0)
				{
					// Empty cell - just background
					for (int k = 0; k < cell_width; k++)
						addch(' ');
				}
				else if (row >= cell_height / 2 - 2 && row <= cell_height / 2 + 2)
				{
					// ASCII art number (5 rows for better quality)
					int ascii_row = row - (cell_height / 2 - 2);
					int digits = get_num_digits(value);
					int digit_width = 5; // Width per digit in ASCII art
					int total_width = digits * digit_width;
					int padding = (cell_width - total_width) / 2;

					// Left padding
					for (int k = 0; k < padding; k++)
						addch(' ');

					// Draw each digit at the correct position (only this row)
					int temp = value;
					int divisor = 1;
					for (int d = 1; d < digits; d++)
						divisor *= 10;

					for (int d = 0; d < digits; d++)
					{
						int digit = (temp / divisor) % 10;
						// Draw only the current row of this digit
						for (int col = 0; col < 5; col++)
						{
							const uint8_t digit_bits[10][5] = {
								{0b01110, 0b10001, 0b10001, 0b10001, 0b01110}, // 0
								{0b00100, 0b01100, 0b00100, 0b00100, 0b01110}, // 1
								{0b01110, 0b10001, 0b00010, 0b00100, 0b11111}, // 2
								{0b01110, 0b10001, 0b00110, 0b10001, 0b01110}, // 3
								{0b10010, 0b10010, 0b11111, 0b00010, 0b00010}, // 4
								{0b11111, 0b10000, 0b11110, 0b00001, 0b11110}, // 5
								{0b01110, 0b10000, 0b11110, 0b10001, 0b01110}, // 6
								{0b11111, 0b00010, 0b00100, 0b01000, 0b01000}, // 7
								{0b01110, 0b10001, 0b01110, 0b10001, 0b01110}, // 8
								{0b01110, 0b10001, 0b01111, 0b00001, 0b01110}  // 9
							};
							if (digit_bits[digit][ascii_row] & (1 << (4 - col)))
								addch('#');
							else
								addch(' ');
						}
						temp %= divisor;
						divisor /= 10;
					}

					// Right padding
					int remaining = cell_width - padding - total_width;
					for (int k = 0; k < remaining; k++)
						addch(' ');
				}
				else
				{
					// Empty row
					for (int k = 0; k < cell_width; k++)
						addch(' ');
				}
				
				if (has_colors())
					attroff(COLOR_PAIR(color));
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

static int	get_color_pair(int value)
{
	if (value == 0) return 1;
	if (value == 2) return 2;
	if (value == 4) return 3;
	if (value == 8) return 4;
	if (value == 16) return 5;
	if (value == 32) return 6;
	if (value == 64) return 7;
	if (value == 128) return 8;
	if (value == 256) return 9;
	if (value == 512) return 10;
	if (value == 1024) return 11;
	if (value == 2048) return 12;
	if (value == 4096) return 13;
	if (value == 8192) return 14;
	if (value == 16384) return 15;
	return 16; // 32768+
}