/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/06 12:06:35 by ebouvier         ###   ########.fr       */
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

static void	execute(t_minishell *minishell, char *line)
{
	t_lexer	*lex;

	if (*line == '\0' || str_all_space(line))
		return (free(line));
	add_history(line);
	lex = lexer(line);
	free(line);
	minishell->root = parse(minishell, lex);
	delete_lexer(lex);
	prep_exec(minishell);
	ast_delete(minishell->root);
	minishell->root = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)argv;
	(void)argc;
	init_minishell(&minishell, env);
	set_shlevel(&minishell);
	while (1)
	{
		line = prompt();
		if (!line)
		{
			if (isatty(0) == 1)
				ft_printf("exit\n");
			return (free_minishell(&minishell), minishell.last_status);
		}
		execute(&minishell, line);
	}
	return (0);
}
