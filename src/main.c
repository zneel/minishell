/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:30:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/23 14:20:24 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_lexer	*lexed;

	(void)argc;
	(void)argv;
	lexed = lexer("echo 'echo \"hello world\"'");
	debug_lexer(lexed);
	delete_lexer(lexed);
	return (0);
}
