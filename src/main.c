/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 00:47:31 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	main(int argc, char **argv)
{
	char	*logname;
	char	*name;
	char *line;
	char *prompt_str;

	(void)argc;
	(void)argv;
	logname = getenv("LOGNAME");
	name = getenv("NAME");
	prompt_str = ft_strjoin(logname, name);
	while (1)
	{
		line = readline(prompt_str);
		lexer(line);
		free(line);
	}
	return (0);
}
