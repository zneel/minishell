NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS+=-g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS+=-fsanitize=address
endif

INCLUDES = -Iinclude -Ilibft/includes
LIBS = -Llibft -lft

SRC=src/main.c
OBJ=$(SRC:.c=.o)
MMD=$(SRC:.c=.d)
LIBRARY=libft/libft.a

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY):
	make -j8 -C libft

clean:
	rm -f $(OBJ) $(MMD)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re