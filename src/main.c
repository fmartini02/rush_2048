#include "2048.h"

int	g_sigint_pressed;

static void	signal_handler(int signal);

int	main()
{
	signal(SIGINT, signal_handler);

	// Just for development
	if (false)
	{
		test_move();
		return (0);
	}

	// Initialize ncurses
	initscr();
	clear();
	noecho();
	cbreak();
	halfdelay(1);  // Make getch() timeout after 0.1 seconds
	curs_set(0);  // Hide cursor
	keypad(stdscr, TRUE);

	render_menù();

	endwin();
	return (0);
}

static void	signal_handler(int signal)
{
	// Ctrl+C
	if (signal == SIGINT)
		g_sigint_pressed = true;
}
