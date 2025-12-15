NAME		= 2048

NCURSES = -lncurses

VALGRIND =  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=definite

INCLUDES = -I./includes

SRC = src/main.c \
		src/utils.c \
# 		src/ui/menù.c \
# 		src/ui/game.c \
# 		src/game/game_logic.c

FLAGS	= -g -O3
# FLAGS	+= -Wall -Werror -Wextra

$(NAME): $(SRC)
	@cc $(SRC) $(INCLUDES) $(NCURSES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t PROJECT COMPILED$(RESET)"

all:$(NAME)

clean:
	@echo "$(RED)[$(NAME)]:\t CLEANED$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

args =

test: all
	 ./$(NAME) $(args)

val: all
	$(VALGRIND) ./$(NAME) $(args)


.PHONY: download

#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m
