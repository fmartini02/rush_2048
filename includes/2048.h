#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
# include <signal.h>

#define ESC 27
#define DIR_UP (1 << 0)
#define DIR_DOWN (1 << 1)
#define DIR_LEFT (1 << 2)
#define DIR_RIGHT (1 << 3)
#define DIR_NONE (1 << 4)

extern int	g_sigint_pressed;


typedef struct	s_game
{
	int		**board;
	int		score;
	int		size;
	bool	can_move;
	bool	added;
} t_game;


t_game	*init_new_game(int size);

int		make_move(t_game *game, int direction);
void	test_move(); // TO DO REMOVE

void	add_random_tile(t_game *game);

void	free_game(t_game *game);

void	render_menù();

int		render_game(t_game *game);
