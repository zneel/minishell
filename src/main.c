/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/26 23:16:10 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "lists.h"
#include "minishell.h"
#include "parser.h"

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = env_cpy(env);
	minishell->pids = NULL;
	minishell->root = NULL;
	minishell->last_status = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	t_lexer		*lexed;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, env);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			free_minishell(&minishell);
			return (0);
		}
		if (line && *line && !ft_isspace(*line))
			add_history(line);
		lexed = lexer(line);
		free(line);
		debug_lexer(lexed);
		minishell.root = parse(lexed);
		delete_lexer(lexed);
		prep_exec(&minishell);
		ast_delete(minishell.root);
		minishell.root = NULL;
		printf("last = %d\n", minishell.last_status);
	}
	return (0);
}
