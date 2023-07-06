/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:05:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 09:49:49 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	shift(t_parser *parser);
void	reduce(t_parser *parser);

void	consume_token(t_parser *parser, t_lexer *lexer)
{
	if (lexer && lexer->token_lst)
	{
		if (lexer->token_lst->next)
			parser->current_tok = lexer->token_lst;
	}
}

int	init_parser(t_parser *parser)
{
	parser->current_tok = NULL;
	parser->parse_stack = malloc(sizeof(t_stack));
	parser->root = NULL;
	if (!parser->parse_stack)
		return (0);
	parser->parse_state = 0;
}

t_node	*parse(t_lexer *lexer)
{
	t_parser	parser;

	if (!init_parser(&parser))
		return (NULL);
	return (parser.root);
}
