/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/14 15:03:21 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "lists.h"
#include "minishell.h"
#include "parser.h"
#include "signaux.h"

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = env_cpy(env);
	minishell->pids = NULL;
	minishell->root = NULL;
	minishell->last_status = -1;
	minishell->std[0] = dup(STDIN_FILENO);
	minishell->std[1] = dup(STDOUT_FILENO);
}

void	execute(t_minishell *minishell, char *line)
{
	t_lexer	*lex;

	lex = lexer(line);
	debug_lexer(lex);
	free(line);
	minishell->root = parse(lex);
	delete_lexer(lex);
	prep_exec(minishell);
	ast_delete(minishell->root);
	minishell->root = NULL;
	prep_exec(minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
	init_minishell(&minishell, env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (free_minishell(&minishell), 0);
		if (line && *line && !ft_isspace(*line))
			add_history(line);
		execute(&minishell, line);
		printf("last = %d\n", minishell.last_status);
	}
	return (0);
}
