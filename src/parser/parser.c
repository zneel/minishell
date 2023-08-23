/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:05:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/22 19:48:24 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "parser.h"

t_bool	accept(t_parser *parser, t_type type)
{
	if (type == parser->current_tok->type)
	{
		parser->current_tok = parser->current_tok->next;
		return (true);
	}
	return (false);
}

t_bool	peek(t_parser *parser, t_type type)
{
	if (type == parser->current_tok->type)
		return (true);
	return (false);
}

t_bool	expect(t_parser *parser, t_type type)
{
	if (accept(parser, type))
		return (true);
	return (false);
}

int	init_parser(t_parser *parser, t_lexer *lexer)
{
	if (lexer->token_lst == NULL)
		return (false);
	parser->current_tok = lexer->token_lst;
	parser->parse_state = 0;
	parser->lexer = lexer;
	return (true);
}

t_node	*parse(t_lexer *lexer)
{
	t_parser	parser;
	t_node		*root;

	if (!lexer)
		return (NULL);
	if (!init_parser(&parser, lexer))
		return (NULL);
	root = parse_grammar(&parser);
	if (!root)
		return (NULL);
	return (root);
}
