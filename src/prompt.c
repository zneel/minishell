/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:40:33 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/01 10:39:12 by mhoyer           ###   ########.fr       */
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

char	*prompt(void)
{
	char	*input;
	char	*line;

	set_signals();
	if (isatty(STDIN_FILENO))
		input = readline("minishell$ ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}
