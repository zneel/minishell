/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:05:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/13 09:52:10 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_parser_error(t_parser *parser, t_error error)
{
	parser->error |= error;
}

int	accept(t_parser *parser, t_type type)
{
	if (type == parser->current_tok->type)
	{
		parser->current_tok = parser->current_tok->next;
		return (1);
	}
	return (0);
}

int	peek(t_parser *parser, t_type type)
{
	if (type == parser->current_tok->next->type)
		return (1);
	return (0);
}

int	expect(t_parser *parser, t_type type)
{
	if (accept(parser, type))
		return (1);
	set_parser_error(parser, SYNTAX_ERROR);
	return (0);
}

int	init_parser(t_parser *parser)
{
	parser->current_tok = NULL;
	parser->root = NULL;
	parser->parse_state = 0;
	parser->error = NO_ERROR;
	return (1);
}

t_node	*parse(t_lexer *lexer)
{
	t_parser	parser;

	if (!lexer)
		return (NULL);
	init_parser(&parser);
	parse_group(&parser);
	return (parser.root);
}
