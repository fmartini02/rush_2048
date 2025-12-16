#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#define ESC 27
#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_LEFT 3
#define DIR_RIGHT 4
#define DIR_NONE 5

extern int	g_sigint_pressed;

enum	e_const
{
	WIN_VALUE = 2048
};


typedef struct	s_game
{
	int		**board;
	int		score;
	int		size;
	bool	moved;
	bool	can_move;
	bool	added;

	// Used to track if win message has been displayed
	//	and allow continuing the game after winning
	bool	win_displayed;

	enum e_const	win_condition;
} t_game;

//START G_C
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_malloc(size_t size, bool CLEAN);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));

t_game	*init_new_game(int size);
//END G_C

int		make_move(t_game *game, int direction);

void	add_random_tile(t_game *game);

void	free_game(t_game *game);

void	render_menù();

int		render_game(t_game *game);

int		load_best_score();

void	save_best_score(int score);
