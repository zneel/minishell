/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:58 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 15:44:04 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->token_lst = NULL;
	lexer->token_count = 0;
	lexer->line = str;
	lexer->line_len = ft_strlen(str);
	lexer->read_pos = 0;
	lexer->curr_pos = lexer->read_pos;
	lexer->curr_char = lexer->line[lexer->read_pos];
	lexer->read_pos++;
	return (lexer);
}

char	lexer_peek(t_lexer *lexer)
{
	if (lexer->read_pos >= lexer->line_len)
		return ('\0');
	else
		return (lexer->line[lexer->read_pos]);
}

void	advance(t_lexer *lexer)
{
	if (lexer->read_pos >= lexer->line_len)
		lexer->curr_char = '\0';
	else
		lexer->curr_char = lexer->line[lexer->read_pos];
	lexer->curr_pos = lexer->read_pos;
	lexer->read_pos++;
}

void	advance_twice(t_lexer *lexer)
{
	advance(lexer);
	advance(lexer);
}

t_lexer	*lexer(char *str)
{
	t_lexer	*lexer;

	lexer = init_lexer(str);
	if (!lexer)
		return (NULL);
	if (!validate(lexer))
	{
		delete_lexer(lexer);
		return (NULL);
	}
	while (lexer->curr_char)
	{
		if (ft_isspace(lexer->curr_char))
		{
			advance(lexer);
			continue ;
		}
		add_token(lexer, next_token(lexer));
	}
	add_token(lexer, new_token(T_EOF, NULL));
	return (lexer);
}
