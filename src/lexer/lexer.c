/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:58 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/25 10:11:23 by ebouvier         ###   ########.fr       */
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
	return (lexer);
}

static char	peek(t_lexer *lexer)
{
	if (lexer->read_pos >= lexer->line_len)
		return ('\0');
	else
		return (lexer->line[lexer->read_pos]);
}

static void	advance(t_lexer *lexer)
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

t_bool	is_special_char(t_lexer *lexer)
{
	if (lexer->curr_char == '|' || (lexer->curr_char == '&'
			&& peek(lexer) == '&') || (lexer->curr_char == '|'
			&& peek(lexer) == '|') || lexer->curr_char == '('
		|| lexer->curr_char == ')' || lexer->curr_char == '<'
		|| lexer->curr_char == '>' || lexer->curr_char == '\0')
		return (true);
	return (false);
}

void	escape_quotes(t_lexer *lexer)
{
	char	quote;

	quote = 0;
	while (lexer->curr_char && !(quote == 0 && ft_isspace(lexer->curr_char)))
	{
		if (lexer->curr_char == QUOTE || lexer->curr_char == DQUOTE)
		{
			if (quote == 0)
				quote = lexer->curr_char;
			else if (quote == lexer->curr_char)
				quote = 0;
		}
		if (is_special_char(lexer) && quote == 0)
			break ;
		advance(lexer);
	}
}

char	*handle_word(t_lexer *lexer)
{
	size_t	start;
	ssize_t	len;
	char	*word;

	start = lexer->curr_pos;
	escape_quotes(lexer);
	len = lexer->curr_pos - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, lexer->line + start, len + 1);
	return (word);
}

t_token	*next_token(t_lexer *lexer)
{
	if (lexer->curr_char == '|' && peek(lexer) == '|')
		return (advance_twice(lexer), new_token(T_OR, NULL));
	else if (lexer->curr_char == '&' && peek(lexer) == '&')
		return (advance_twice(lexer), new_token(T_AND, NULL));
	else if (lexer->curr_char == '|')
		return (advance(lexer), new_token(T_PIPE, NULL));
	else if (lexer->curr_char == '(')
		return (advance(lexer), new_token(T_LPAREN, NULL));
	else if (lexer->curr_char == ')')
		return (advance(lexer), new_token(T_RPAREN, NULL));
	else if (lexer->curr_char == '>' && peek(lexer) == '>')
		return (advance_twice(lexer), new_token(T_DGREAT, NULL));
	else if (lexer->curr_char == '<' && peek(lexer) == '<')
		return (advance_twice(lexer), new_token(T_DLESS, NULL));
	else if (lexer->curr_char == '>')
		return (advance(lexer), new_token(T_GREAT, NULL));
	else if (lexer->curr_char == '<')
		return (advance(lexer), new_token(T_LESS, NULL));
	else if (ft_isascii(lexer->curr_char) && lexer->curr_char != '\0')
		return (new_token(T_WORD, handle_word(lexer)));
	return (NULL);
}

t_lexer	*lexer(char *str)
{
	t_lexer	*lexer;

	lexer = init_lexer(str);
	if (!lexer)
		return (NULL);
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
