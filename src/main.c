/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/24 16:36:18 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_lexer	*lexed;
	char *line;

	(void)argc;
	(void)argv;
	// lexed = lexer("echo 'echo \"hello &&world\"' | grep world || bon' 'jour && false");
	while (1)
	{
		line = readline("minishel> ");
		if (!line)
			return (1);
		lexed = lexer(line);
		debug_lexer(lexed);
		delete_lexer(lexed);
	}
	return (0);
}
