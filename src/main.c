#include "2048.h"

int	g_sigint_pressed;

static void	signal_handler(int signal);
static void	cleanup(void);

int	main()
{
	// Check that the WIN_VALUE is a power of two
	if (WIN_VALUE <= 0 || (WIN_VALUE & (WIN_VALUE - 1)) != 0)
	{
		int	n = write(STDERR_FILENO, "Error: WIN_VALUE must be a power of two greater than 0.\n", 57);
		return (1);
	}

	signal(SIGINT, signal_handler);
	atexit(cleanup);

	// Initialize ncurses
	initscr();
	clear();
	noecho();
	cbreak();
	halfdelay(1);  // Make getch() timeout after 0.1 seconds
	curs_set(0);  // Hide cursor
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse events to catch scroll wheel
	mouseinterval(0);
	
	// Initialize colors
	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_WHITE);      // 0 (empty)
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);     // 2
		init_pair(3, COLOR_BLACK, COLOR_GREEN);      // 4
		init_pair(4, COLOR_WHITE, COLOR_BLUE);       // 8
		init_pair(5, COLOR_WHITE, COLOR_MAGENTA);    // 16
		init_pair(6, COLOR_WHITE, COLOR_CYAN);       // 32
		init_pair(7, COLOR_BLACK, COLOR_RED);        // 64
		init_pair(8, COLOR_YELLOW, COLOR_RED);       // 128
		init_pair(9, COLOR_YELLOW, COLOR_MAGENTA);   // 256
		init_pair(10, COLOR_YELLOW, COLOR_BLUE);     // 512
		init_pair(11, COLOR_BLACK, COLOR_YELLOW);    // 1024
		init_pair(12, COLOR_WHITE, COLOR_BLACK);     // 2048+
	}

	render_menù();

	return (0);
}

static void	cleanup(void)
{
	ft_malloc(0, 1);
	endwin();
}

static void	signal_handler(int signal)
{
	// Ctrl+C
	if (signal == SIGINT)
	{
		g_sigint_pressed = true;
		endwin();
		exit(0);
	}
}
