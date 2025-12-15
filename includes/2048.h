#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
# include <signal.h>

extern int	g_sigint_pressed;

typedef struct	s_game
{
	int	**board;
	int	size;
	int	game_over;
} t_game;

t_game	*init_new_game(int size);

void	free_game(t_game *game);

void	render_menù();

int		render_game(t_game *game);
