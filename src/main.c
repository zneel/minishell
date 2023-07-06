/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 09:49:24 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"
#include "builtin.h"

int	main(int argc, char **argv, char **env)
{
	t_lexer		*lexed;
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	minishell.env = env_cpy(env);
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
