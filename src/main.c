/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 10:47:45 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_lexer		*lexed;
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	minishell.env = env_cpy(env);
	(void)minishell;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			return (1);
		lexed = lexer(line);
		debug_lexer(lexed);
		delete_lexer(lexed);
	}
	return (0);
}
