/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:05:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/28 13:00:43 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "parser.h"

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
