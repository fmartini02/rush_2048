# include <stdlib.h>
# include <ncurses.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>

#define SIZE 4
#define ESC 27
#define DIR_UP (1 << 0)
#define DIR_DOWN (1 << 1)
#define DIR_LEFT (1 << 2)
#define DIR_RIGHT (1 << 3)
#define DIR_NONE (1 << 4)

extern int	g_sigint_pressed;

typedef struct {
	int		board[SIZE][SIZE];
	int		score;
	int		game_over;
	bool	esc;
	bool	can_move;
	uint8_t	bit_flag;
} t_game;
