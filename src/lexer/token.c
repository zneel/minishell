/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:16:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 15:41:32 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	if (value)
		token->len = ft_strlen(value);
	else
		token->len = 0;
	token->next = NULL;
	return (token);
}

t_token	*next_token(t_lexer *lexer)
{
	if (lexer->curr_char == '|' && lexer_peek(lexer) == '|')
		return (advance_twice(lexer), new_token(T_OR, NULL));
	else if (lexer->curr_char == '&' && lexer_peek(lexer) == '&')
		return (advance_twice(lexer), new_token(T_AND, NULL));
	else if (lexer->curr_char == '|')
		return (advance(lexer), new_token(T_PIPE, NULL));
	else if (lexer->curr_char == '(')
		return (advance(lexer), new_token(T_LPAREN, NULL));
	else if (lexer->curr_char == ')')
		return (advance(lexer), new_token(T_RPAREN, NULL));
	else if (lexer->curr_char == '>' && lexer_peek(lexer) == '>')
		return (advance_twice(lexer), new_token(T_DGREAT, NULL));
	else if (lexer->curr_char == '<' && lexer_peek(lexer) == '<')
		return (advance_twice(lexer), new_token(T_DLESS, NULL));
	else if (lexer->curr_char == '>')
		return (advance(lexer), new_token(T_GREAT, NULL));
	else if (lexer->curr_char == '<')
		return (advance(lexer), new_token(T_LESS, NULL));
	else if (ft_isascii(lexer->curr_char) && lexer->curr_char != '\0')
		return (new_token(T_WORD, handle_word(lexer)));
	return (NULL);
}

void	add_token(t_lexer *lexer, t_token *token)
{
	t_token	*curr;

	curr = lexer->token_lst;
	if (!curr)
		lexer->token_lst = token;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = token;
	}
	lexer->token_count++;
}
