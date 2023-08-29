/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/29 22:06:22 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "expand.h"
#include "lexer.h"
#include "lists.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = env_cpy(env);
	minishell->pids = NULL;
	minishell->root = NULL;
	minishell->last_status = 0;
	minishell->std[0] = dup(STDIN_FILENO);
	minishell->std[1] = dup(STDOUT_FILENO);
}

static void	execute(t_minishell *minishell, char *line)
{
	t_lexer	*lex;

	lex = lexer(line);
	free(line);
	minishell->root = parse(lex);
	// debug_lexer(lex);
	// pretty_print_ast(minishell->root, "");
	delete_lexer(lex);
	prep_exec(minishell);
	ast_delete(minishell->root);
	minishell->root = NULL;
}

int	str_all_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			return (0);
	}
	return (1);
}

int	execute_inline(char **argv, t_minishell *minishell)
{
	char	*line;

	line = ft_strdup(argv[2]);
	execute(minishell, line);
	return (free_minishell(minishell), 0);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)argv;
	init_minishell(&minishell, env);
	if (argc > 1 && ft_strncmp(argv[1], "-c", 2) == 0)
		return (execute_inline(argv, &minishell));
	while (1)
	{
		signal(SIGINT, sig_handler_minishell);
		signal(SIGQUIT, sig_handler_minishell);
		if (g_sigint == 1)
			dup2(minishell.std[0], 0);
		line = readline("minishell> ");
		g_sigint = 0;
		if (!line)
			return (free_minishell(&minishell), 0);
		if (line && *line && !str_all_space(line))
		{
			add_history(line);
			execute(&minishell, line);
		}
	}
	return (0);
}
