#include "2048.h"

static size_t	count_digits(long int num);
static void		*ft_bzero(void *b, size_t len);
static void		*ft_calloc(size_t nitems, size_t size);
static size_t	ft_strlen(const char *s);
char			*ft_itoa(int n);

t_game	*init_new_game(int size)
{
	t_game	*game;

	game = (t_game *)ft_malloc(sizeof(t_game), 0);
	if (!game)
		return (NULL);

	game->size = size;
	game->score = 0;

	game->can_move = true;
	game->added = false;

	game->win_displayed = false;

	game->win_condition = WIN_VALUE;

	game->board = ft_malloc(sizeof(int *) * size, 0);
	for (int i = 0; i < size; i++)
	{
		game->board[i] = ft_malloc(sizeof(int) * size, 0);
		// Initialize all cells to 0
		for (int j = 0; j < size; j++)
			game->board[i][j] = 0;
	}

	// the game starts with two tiles
	add_random_tile(game);
	add_random_tile(game);

	return (game);
}

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}

void add_random_tile(t_game *game)
{
	int empty_cells[game->size * game->size][2];
	int empty_count = 0;
	int i, j;

	for (i = 0; i < game->size; i++)
	{
		for (j = 0; j < game->size; j++)
		{
			if (game->board[i][j] == 0)
			{
				empty_cells[empty_count][0] = i;
				empty_cells[empty_count][1] = j;
				empty_count++;
			}
		}
	}

	if (empty_count == 0)
		return;

	int rand_index = rand() % empty_count;
	int row = empty_cells[rand_index][0];
	int col = empty_cells[rand_index][1];

	game->board[row][col] = (rand() % 10 == 0) ? 4 : 2;
	game->added = 1;
}

int	load_best_score()
{
	int		fd;
	int		best_score = 0;
	char	buffer[32];
	ssize_t	bytes_read;

	fd = open(".2048_best_score", O_RDONLY);
	if (fd != -1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			best_score = atoi(buffer);
		}
		close(fd);
	}
	return (best_score);
}

void	save_best_score(int score)
{
	int		fd;
	int		current_best;
	char	*buffer;
	int		len;

	current_best = load_best_score();
	if (score > current_best)
	{
		fd = open(".2048_best_score", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
		{
			buffer = ft_itoa(score);
			len = ft_strlen(buffer);
			write(fd, buffer, len);
			close(fd);
		}
	}
}

//-------------------------------------------------------HELPERS FOR FT_ITOA

static size_t	count_digits(long int num)
{
	size_t		count;

	count = 1;
	if (num < 0)
	{
		count++;
		num = -num;
	}
	while (num >= 10)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static char	*reverse_string(char *s, int s_length)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = s_length - 1;
	while (i < (s_length / 2))
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
	return (s);
}

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = dest;
	i = 0;
	while (i < count)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}

void	*ft_bzero(void *dest, size_t count)
{
	return (ft_memset(dest, '\0', count));
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*tmp;

	tmp = ft_malloc(nitems * size, 0);
	if (!tmp)
		return (NULL);
	return (ft_bzero(tmp, nitems * size));
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	size_t		digits_count;
	long int	ln;

	ln = n;
	digits_count = count_digits(ln);
	res = ft_calloc(sizeof(char) * (digits_count + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (ln < 0)
	{
		ln = -ln;
		res[digits_count - 1] = '-';
	}
	i = 0;
	while (ln >= 10)
	{
		res[i] = (ln % 10) + 48;
		ln /= 10;
		i++;
	}
	res[i] = (ln % 10) + 48;
	return (reverse_string(res, digits_count));
}
