/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/05 16:43:28 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_lexer	*lexed;
	char	*line;

	(void)argc;
	(void)argv;
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
