NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror

RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
PINK      = \033[38;5;206m
YELLOW  = \033[33m
BLUE    = \033[34m

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
	@echo "$(PINK)"
	@echo "	==================================================================="
	@echo "	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "	==================================================================="
	@echo "$(RESET)"
	@echo "$(BLUE)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compilation completed!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null
	@echo "$(GREEN)$< compiled successfully!$(RESET)"

$(LIBRARY):
	@echo "$(BLUE)Compiling library...$(RESET)"
	@make -j8 -C libft > /dev/null
	@echo "$(GREEN)Library compilation completed!$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@rm -f $(OBJ) $(MMD) > /dev/null
	@make -C libft clean > /dev/null
	@echo "$(GREEN)Clean-up completed!$(RESET)"

fclean: clean
	@rm -f $(NAME) > /dev/null
	@make -C libft fclean > /dev/null

re: fclean all

.PHONY: all clean fclean re



                                                                   
