#include "2048.h"

extern int	g_sigint_pressed;

static int	render_size_choice_menu();

void	render_menù()
{
	int	choice = 0;
	int	highlight = 0;

	int		n_options = 3;
	char	*options[] =
	{
		"New Game",
		"Continue",
		"Exit"
	};

	static t_game	*saved_game = NULL;  // Store game when ESC is pressed

	clear();  // Clear screen when entering menu

	while (!g_sigint_pressed)
	{
		// Display menu
		for (int i = 0; i < n_options; i++)
		{
			if (i == highlight)
				attron(A_REVERSE);  // Highlight selected option

			// Print the option intendedly
			mvprintw(5 + i, 10, "%s", options[i]);
			// Turn off highlight
			attroff(A_REVERSE);
		}
		refresh();

		// Get input
		choice = getch();

		if (g_sigint_pressed)
			break;

		// Ignore timeout (ERR = -1)
		if (choice == ERR)
			continue;

		switch (choice)
		{
			// Exit
			case ESC:
				free_game(saved_game);
				return;

			case KEY_UP:
				highlight = (highlight - 1 + n_options) % n_options;
				// Skip Continue if no saved game
				if (highlight == 1 && saved_game == NULL)
					highlight = (highlight - 1 + n_options) % n_options;
				break;

			case KEY_DOWN:
				highlight = (highlight + 1) % n_options;
				// Skip Continue if no saved game
				if (highlight == 1 && saved_game == NULL)
					highlight = (highlight + 1) % n_options;
				break;

			case 10:  // Enter key
				if (highlight == n_options - 1)  // Exit selected
				{
					free_game(saved_game);
					return;
				}

				if (highlight == 0)  // New Game selected
				{
					// Free old saved game if exists
					free_game(saved_game);
					saved_game = NULL;

					int	size = render_size_choice_menu();
					if (size == -1)
					{
						clear();
						continue;  // Back to main menu
					}

					t_game	*game = init_new_game(size);
					int		result = render_game(game);  // Returns: 0=ESC, 1=game_over

					if (result == 0)  // ESC pressed - save game
						saved_game = game;
					else  // Game over - free game
						free_game(game);

					clear();
				}
				else if (highlight == 1)  // Continue selected
				{
					if (saved_game != NULL)
					{
						int	result = render_game(saved_game);
						if (result == 1)  // Game over - free game
						{
							free_game(saved_game);
							saved_game = NULL;
						}
						clear();
					}
					else
					{
						// This should not happen due to skipping logic
						mvprintw(10, 10, "No saved game to continue!");
						refresh();
						clear();
					}
				}

				break;
		}
	}
}

// Return the chosen size, or -1 if going back to main menu
static int	render_size_choice_menu(void)
{
	int	choice = 0;
	int	highlight = 0;

	int		n_options = 3;
	char	*options[] =
	{
		"3x3",
		"4x4",
		"Back to Main Menu"
	};

	clear();  // Clear screen when entering size choice menu

	while (!g_sigint_pressed)
	{
		// Display menu
		for (int i = 0; i < n_options; i++)
		{
			if (i == highlight)
				attron(A_REVERSE);  // Highlight selected option

			// Print the option intendedly
			mvprintw(5 + i, 10, "%s", options[i]);
			// Turn off highlight
			attroff(A_REVERSE);
		}
		refresh();

		// Get input
		choice = getch();

		if (g_sigint_pressed)
			return (-1);

		// Ignore timeout (ERR = -1)
		if (choice == ERR)
			continue;

		switch (choice)
		{
			case ESC:  // go back
				return (-1);

			case KEY_UP:
				highlight = (highlight - 1 + n_options) % n_options;
				break;

			case KEY_DOWN:
				highlight = (highlight + 1) % n_options;
				break;

			case 10:  // Enter key
				if (highlight == n_options - 1)  // Back to Main Menu selected
				{
					clear();
					render_menù();
					return (-1);
				}

				int	size = (highlight == 0) ? 3 : 4;
				return (size);

				break;
		}
	}

	return (-1);
}
