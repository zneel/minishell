/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/23 14:45:16 by ebouvier         ###   ########.fr       */
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
	debug_lexer(lex);
	expand_tree(minishell->root, minishell);
	pretty_print_ast(minishell->root, "");
	delete_lexer(lex);
	prep_exec(minishell);
	ast_delete(minishell->root);
	minishell->root = NULL;
	prep_exec(minishell);
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

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, env);
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
			add_history(line);
		execute(&minishell, line);
		printf("last = %d\n", minishell.last_status);
	}
	return (0);
}
