
NAME = exo5

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = A.c B.c prog.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

A.o: A.h
B.o: A.h B.h
prog.o: A.h B.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
