CC = gcc

C_FLAGS = -Wall -Wextra -Werror -g -I .

C_FLAGS  += $(shell pkg-config --cflags sdl2)
LDLIBS  = $(shell pkg-config --libs sdl2)

NAME = bj

C_FILES = blackjack.c \

O_FILES = $(C_FILES:.c=.o)

all: $(NAME)

$(NAME):$(O_FILES)
	gcc $(C_FLAGS) $(O_FILES) -o $(NAME) $(LDLIBS)

%.o: %.c
	gcc -c $(C_FLAGS) $< -o $@

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(O_FILES)

.PHONY: all clean fclean re
