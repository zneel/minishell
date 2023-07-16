/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/24 19:02:07 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	t_lexer		*lexed;
	char		*line;

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
		debug_lexer(lexed);
		delete_lexer(lexed);
	}
	free_minishell(&minishell);
	return (0);
}
