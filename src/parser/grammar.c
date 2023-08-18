/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:17:18 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 15:49:33 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>

t_node	*pipeline(t_parser *parser)
{
	t_node	*left_node;
	t_node	*pipe_node;
	t_node	*right_node;

	left_node = command(parser);
	if (!left_node)
		return (NULL);
	while (accept(parser, T_PIPE))
	{
		pipe_node = new_node(PIPE);
		if (!pipe_node)
			return (ast_delete(left_node), NULL);
		right_node = command(parser);
		if (!right_node)
		{
			ast_attach_binary(pipe_node, left_node, right_node);
			return (ast_delete(pipe_node), NULL);
		}
		ast_attach_binary(pipe_node, left_node, right_node);
		left_node = pipe_node;
	}
	return (left_node);
}

t_node	*expr(t_parser *parser)
{
	t_node	*node;

	node = NULL;
	if (accept(parser, T_LPAREN))
	{
		stack_push(&parser->parse_stack, (void *)LPAREN);
		node = group(parser);
		if (!node)
			return (NULL);
		return (node);
	}
	node = pipeline(parser);
	if (!node)
		return (NULL);
	return (node);
}

t_node	*command_line(t_parser *parser)
{
	t_node	*left_node;
	t_node	*logical_node;
	t_node	*right_node;

	logical_node = NULL;
	left_node = expr(parser);
	if (!left_node)
		return (NULL);
	while (peek(parser, T_AND) || peek(parser, T_OR))
	{
		logical_node = new_node(lexer_to_node(parser->current_tok->type));
		accept(parser, parser->current_tok->type);
		if (!logical_node)
			return (ast_delete(left_node), NULL);
		right_node = expr(parser);
		if (!right_node)
			return (ast_delete(left_node), ast_delete(logical_node), NULL);
		ast_attach_binary(logical_node, left_node, right_node);
		left_node = logical_node;
	}
	if (logical_node)
		return (logical_node);
	return (left_node);
}

t_node	*parse_grammar(t_parser *parser)
{
	t_node	*root;

	root = NULL;
	if (parser->current_tok->type == T_EOF)
		return (NULL);
	root = command_line(parser);
	if (parser->current_tok->type != T_EOF)
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
				token_to_str(parser->current_tok->type));
		ast_delete(root);
		return (NULL);
	}
	if (!root)
		return (NULL);
	return (root);
}
