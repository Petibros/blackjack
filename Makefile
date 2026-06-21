CC = gcc

C_FLAGS = -Wall -Wextra -Werror -g -I inc/

NAME = blackjack

C_FILES = src/blackjack.c \
		  src/game_prep.c \
		  src/game_turn.c \
		  src/game_start.c \
		  src/display.c \
		  src/game_end.c

O_FILES = $(C_FILES:.c=.o)

all: $(NAME)

$(NAME):$(O_FILES)
	gcc $(C_FLAGS) $(O_FILES) -o $(NAME)

%.o: %.c
	gcc -c $(C_FLAGS) $< -o $@

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(O_FILES)

run: $(NAME)
	./$(NAME)


.PHONY: all clean fclean re
