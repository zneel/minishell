NAME=minishell
CC=clang
CFLAGS=-Wall -Wextra -Werror -O2 -std=c99 -MMD

RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
PINK	= \033[38;5;206m
YELLOW  = \033[33m
BLUE    = \033[34m

ifeq ($(DEBUG), 1)
	CFLAGS+=-g3
endif

ifeq ($(SAN), 1)
	CFLAGS+=-fsanitize=address
endif

ifeq ($(DEV), 1)
	CFLAGS+=-fsanitize=address -g3
endif

INCLUDES = -Iinclude -Ilibft/includes
LIBS = -Llibft -lft -lreadline

SRC =	src/main.c \
		src/lexer/lexer.c \
		src/lexer/debug.c \
		src/lexer/delete.c \
		src/lexer/token.c \
		src/parser/parser.c \
		src/parser/grammar.c \
		src/parser/utils.c \
		src/parser/ast.c \
		src/builtin/check_builtin.c \
		src/builtin/exec_builtin.c \
		src/builtin/echo.c \
		src/builtin/pwd.c \
		src/builtin/print_env.c \
		src/builtin/export.c \
		src/builtin/unset.c \
		src/env/env_cpy.c \
		src/env/convert_env.c \
		src/env/ft_lstadd_back_env.c \
		src/env/ft_lstclear_env.c \
		src/env/ft_lstdelone_env.c \
		src/env/ft_lstnew_env.c \
		src/env/ft_lstsize_env.c \
		src/env/free_mat.c \
		src/env/ft_lstsort_env.c \
		src/env/ft_lstcpy_env.c \
		src/exec/exec.c \
		src/exec/path.c \
		src/exec/cmd.c \
		src/exec/first_pipe.c \
		src/exec/middle_pipe.c \
		src/exec/last_pipe.c \
		src/exec/pipeline.c \
		src/exec/utils.c \
		src/exec/here_doc.c \
		src/exec/error.c \
		src/exec/exec_mini.c

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
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBRARY) $(LIBS)
	@echo "$(GREEN)Compilation completed!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
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
