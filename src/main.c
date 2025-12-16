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
	timeout(5);  // 5ms timeout for responsive input
	curs_set(0);  // Hide cursor
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse events to catch scroll wheel
	mouseinterval(0);
	
	// Initialize colors
	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_BLACK, COLOR_WHITE);      // 0 (empty) - light gray
		init_pair(2, COLOR_BLACK, COLOR_CYAN);       // 2 - light cyan/blue
		init_pair(3, COLOR_BLACK, COLOR_YELLOW);     // 4 - light yellow
		init_pair(4, COLOR_WHITE, COLOR_YELLOW);     // 8 - orange
		init_pair(5, COLOR_WHITE, COLOR_YELLOW);     // 16 - orange
		init_pair(6, COLOR_WHITE, COLOR_RED);        // 32 - red/coral
		init_pair(7, COLOR_WHITE, COLOR_RED);        // 64 - red
		init_pair(8, COLOR_WHITE, COLOR_YELLOW);     // 128 - yellow
		init_pair(9, COLOR_WHITE, COLOR_YELLOW);     // 256 - yellow
		init_pair(10, COLOR_WHITE, COLOR_YELLOW);    // 512 - yellow
		init_pair(11, COLOR_WHITE, COLOR_YELLOW);    // 1024 - yellow
		init_pair(12, COLOR_BLACK, COLOR_YELLOW);    // 2048 - golden yellow
		init_pair(13, COLOR_BLACK, COLOR_YELLOW);    // 4096 - darker yellow
		init_pair(14, COLOR_WHITE, COLOR_MAGENTA);   // 8192 - purple
		init_pair(15, COLOR_WHITE, COLOR_CYAN);      // 16384 - cyan
		init_pair(16, COLOR_WHITE, COLOR_BLUE);      // 32768+ - blue
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
