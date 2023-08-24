/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:32:44 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 15:43:00 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	is_special_char(t_lexer *lexer)
{
	if (lexer->curr_char == '|' || (lexer->curr_char == '&'
			&& lexer_peek(lexer) == '&') || (lexer->curr_char == '|'
			&& lexer_peek(lexer) == '|') || lexer->curr_char == '('
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
