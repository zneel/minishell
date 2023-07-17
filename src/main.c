/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/26 21:31:15 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "lists.h"
#include "minishell.h"
#include "parser.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	t_lexer		*lexed;
	char		*line;
	t_node		*root;

	(void)argc;
	(void)argv;
	minishell.env = env_cpy(env);
	minishell.pids = NULL;
	minishell.std[0] = dup(STDIN_FILENO);
	minishell.std[1] = dup(STDOUT_FILENO);
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
		root = parse(lexed);
		delete_lexer(lexed);
		prep_exec(root, &minishell);
		ast_delete(root);
		printf("last = %d\n", minishell.last_status);
	}
	free_minishell(&minishell);
	return (0);
}
