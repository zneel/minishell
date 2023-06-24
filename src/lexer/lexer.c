/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:58 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/23 15:31:23 by ebouvier         ###   ########.fr       */
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
	lexer->curr_pos = 0;
	lexer->read_pos = 0;
	lexer->curr_char = '\0';
	return (lexer);
}

void	read_char(t_lexer *lexer)
{
	if (lexer->read_pos >= ft_strlen(lexer->line))
		lexer->curr_char = '\0';
	else
		lexer->curr_char = lexer->line[lexer->read_pos];
	lexer->curr_pos = lexer->read_pos;
	lexer->read_pos++;
}

ssize_t	escape_quote(char *str)
{
	char	current_quote;
	size_t	len;

	current_quote = *str++;
	len = 0;
	while (*str && *str != current_quote)
	{
		len++;
		str++;
	}
	if (!*str)
		return (-1);
	return (len);
}

char	*handle_word(t_lexer *lexer)
{
	size_t	start;
	char	*word;
	ssize_t	len;
	ssize_t	escape_len;

	start = lexer->curr_pos;
	if (lexer->curr_char == QUOTE || lexer->curr_char == DQUOTE)
	{
		len = escape_quote(lexer->line + lexer->curr_pos);
		if (len == -1)
			return (NULL);
		escape_len = len;
		while (escape_len--)
			read_char(lexer);
	}
	else
	{
		while (lexer->curr_char && !ft_isspace(lexer->curr_char))
			read_char(lexer);
		len = lexer->curr_pos - start;
	}
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
	ft_printf("--->input:%s\n", str);
	read_char(lexer);
	while (lexer->curr_char)
	{
		if (!ft_isspace(lexer->curr_char))
			add_token(lexer, next_token(lexer));
		read_char(lexer);
	}
	debug_lexer(lexer);
	return (lexer);
}
