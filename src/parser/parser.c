/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:05:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 09:25:17 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*consume_token(t_parser *parser, t_lexer *lexer)
{
	if (lexer && lexer->token_lst)
	{
		if (lexer->token_lst->next)
		{
			parser->current_tok = lexer->token_lst;
			return (parser->current_tok);
		}
	}
	return (NULL);
}

t_node	*parse(t_lexer *lexer)
{
	t_parser	parser;

	// consume_token();
}
