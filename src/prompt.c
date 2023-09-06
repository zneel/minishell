/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:40:33 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/06 11:42:15 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "get_next_line.h"
#include "minishell.h"
#include "signals.h"
#include "structs.h"

void	set_signals(void)
{
	signal(SIGINT, sig_handler_minishell);
	signal(SIGQUIT, sig_handler_minishell);
}

char	*prompt(void)
{
	char	*input;
	char	*line;

	set_signals();
	if (isatty(STDIN_FILENO))
		input = readline("minishell$ ");
	else
	{
		line = get_next_line(STDIN_FILENO, 1);
		input = ft_strtrim(line, "\n");
		free(line);
		get_next_line(STDIN_FILENO, 0);
	}
	return (input);
}
