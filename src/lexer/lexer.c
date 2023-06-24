/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:58 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/24 16:36:50 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->tok_lst = NULL;
	lexer->tok_count = 0;
	lexer->line = str;
	lexer->line_len = ft_strlen(str);
	lexer->curr_pos = 0;
	lexer->read_pos = 0;
	lexer->curr_char = '\0';
	return (lexer);
}

void	read_char(t_lexer *lexer)
{
	if (lexer->read_pos >= lexer->line_len)
		lexer->curr_char = '\0';
	else
		lexer->curr_char = lexer->line[lexer->read_pos];
	lexer->curr_pos = lexer->read_pos;
	lexer->read_pos++;
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
		read_char(lexer);
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
	char	*word;

	if (lexer->curr_char == '|' && lexer->line[lexer->read_pos] == '|')
		return (read_char(lexer), new_token(TOK_OR, ft_strdup("||"), 2));
	else if (lexer->curr_char == ';')
		return (new_token(TOK_SEMI, ft_strdup(";"), 1));
	else if (lexer->curr_char == '&' && lexer->line[lexer->read_pos] == '&')
		return (read_char(lexer), new_token(TOK_AND, ft_strdup("&&"), 2));
	else if (lexer->curr_char == '|')
		return (new_token(TOK_PIPE, ft_strdup("|"), 1));
	else if (lexer->curr_char == '(')
		return (new_token(TOK_LPAREN, ft_strdup("("), 1));
	else if (lexer->curr_char == ')')
		return (new_token(TOK_RPAREN, ft_strdup(")"), 1));
	else if (lexer->curr_char == '>' && lexer->line[lexer->read_pos] == '>')
		return (read_char(lexer), new_token(TOK_APPEND, ft_strdup(">>"), 2));
	else if (lexer->curr_char == '<' && lexer->line[lexer->read_pos] == '<')
		return (read_char(lexer), new_token(TOK_HEREDOC, ft_strdup("<<"), 2));
	else if (lexer->curr_char == '>')
		return (new_token(TOK_RD_IN, ft_strdup(">"), 1));
	else if (lexer->curr_char == '<')
		return (new_token(TOK_RD_OUT, ft_strdup("<"), 1));
	else if (ft_isascii(lexer->curr_char))
	{
		word = handle_word(lexer);
		return (new_token(TOK_WORD, word, ft_strlen(word)));
	}
	else
		return (new_token(TOK_ERROR, NULL, 0));
}

t_lexer	*lexer(char *str)
{
	t_lexer	*lexer;

	lexer = init_lexer(str);
	if (!lexer)
		return (NULL);
	read_char(lexer);
	while (lexer->curr_char)
	{
		if (!ft_isspace(lexer->curr_char))
			add_token(lexer, next_token(lexer));
		read_char(lexer);
	}
	return (lexer);
}
