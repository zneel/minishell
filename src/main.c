/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/21 14:58:50 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	t_node command1 = {
		.type = COMMAND,
		.raw_command = "cat Makefile",
		.parent = NULL,
		.left = NULL,
		.right = NULL,
	};
	t_node command2 = {
		.type = COMMAND,
		.raw_command = "head",
		.parent = NULL,
		.left = NULL,
		.right = NULL,
	};
	t_node pipe1 = {
		.type = PIPE,
		.left = &command1,
		.right = &command2,
		.parent = NULL,
	};
	command1.parent = &pipe1;
	command2.parent = &pipe1;
	t_node command3 = {
		.type = COMMAND,
		.raw_command = "cat -e",
		.parent = NULL,
		.left = NULL,
		.right = NULL,
	};
	t_node pipe2 = {
		.type = PIPE,
		.left = &pipe1,
		.right = &command3,
		.parent = NULL,
	};
	pipe1.parent = &pipe2;
	command3.parent = &pipe2;
	t_node command4 = {
		.type = COMMAND,
		.raw_command = "grep cc",
		.parent = NULL,
		.left = NULL,
		.right = NULL,
	};
	t_node ast = {
		.type = PIPE,
		.left = &pipe2,
		.right = &command4,
		.parent = NULL,
	};
	pipe2.parent = &ast;
	command4.parent = &ast;
	t_node command1test = {
		.type = COMMAND,
		.raw_command = "yes",
		.parent = NULL,
		.left = NULL,
		.right = NULL,
	};
	t_node command2test = {
		.type = COMMAND,
		.raw_command = "head",
		.parent = NULL,
		.left = NULL,
		.right = NULL,
	};
	t_node test = {
		.type = PIPE,
		.left = &command1test,
		.right = &command2test,
		.parent = NULL,
	};
	command1test.parent = &test;
	command2test.parent = &test;
	(void)argv;
	minishell.env = env_cpy(env);
	if (argc == 1)
		prep_exec(&test, &minishell);
	else
		prep_exec(&ast, &minishell);
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line)
	// 		return (1);
	// 	if (line && *line && *line != ' ' && *line != '\t')
	// 		add_history(line);
	// 	lexed = lexer(line);
	// 	debug_lexer(lexed);
	// 	delete_lexer(lexed);
	// }
	// ft_lstclear_env(&minishell.env, free);
	return (0);
}
