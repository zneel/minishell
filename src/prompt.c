/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:40:33 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/31 13:59:39 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "get_next_line.h"
#include "minishell.h"
#include "signals.h"
#include "structs.h"

static void	set_signals(void)
{
	signal(SIGINT, sig_handler_minishell);
	signal(SIGQUIT, sig_handler_minishell);
}

char	*prompt(t_minishell *minishell)
{
	char	*input;
	char	*line;

	set_signals();
	if (!minishell->env)
		exit(EXIT_FAILURE);
	if (isatty(STDIN_FILENO) == 1)
		input = readline("minishell> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strchr(line, '\n');
		if (input)
			*input = '\0';
		free(line);
	}
	if (!input)
		exit(EXIT_FAILURE);
	return (input);
}
