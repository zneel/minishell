/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/24 19:07:05 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "get_next_line.h"
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
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		if (line && *line && *line != ' ' && *line != '\t')
			add_history(line);
		lexed = lexer(line);
		free(line);
		debug_lexer(lexed);
		root = parse(lexed);
		delete_lexer(lexed);
		ast_delete(root);
	}
	free_minishell(&minishell);
	return (0);
}
