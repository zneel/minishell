/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:17:18 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/14 11:43:18 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "unistd.h"

t_node	*parse_here_end(t_parser *parser)
{
}
t_node	*parse_filename(t_parser *parser)
{
}
t_node	*parse_io_here(t_parser *parser)
{
}
t_node	*parse_io_file(t_parser *parser)
{
}
t_node	*parse_io_redirect(t_parser *parser)
{
}
t_node	*parse_suffix(t_parser *parser)
{
}
t_node	*parse_cmd_word(t_parser *parser)
{
}
t_node	*parse_prefix(t_parser *parser)
{
}
t_node	*parse_command(t_parser *parser)
{
	t_node	*prefix_node;
	t_node	*cmd_word_node;
	t_node	*suffix_node;
	t_node	*io_redirect_node;
	t_node	*new_node;

	prefix_node = parse_prefix(parser);
	if (parser->error & SYNTAX_ERROR)
		return (write(1, "SYNTAX ERROR.\n", 15), NULL);
	cmd_word_node = parse_cmd_word(parser);
	if (parser->error & SYNTAX_ERROR)
		return (write(1, "SYNTAX ERROR.\n", 15), NULL);
	if (expect(parser, T_LESS) || expect(parser, T_GREAT) || expect(parser,
			T_DGREAT) || expect(parser, T_DLESS))
	{
		io_redirect_node = parse_io_redirect(parser);
		if (parser->error & SYNTAX_ERROR)
			return (write(1, "SYNTAX ERROR.\n", 15), NULL);
	}
	else
	{
		suffix_node = parse_suffix(parser);
		if (parser->error & SYNTAX_ERROR)
			return (write(1, "SYNTAX ERROR.\n", 15), NULL);
	}
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = COMMAND;
	ast_attach_binary(new_node, prefix_node, cmd_word_node);
	return (new_node);
}

t_node	*parse_pipeline(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_node;

	left = parse_command(parser);
	if (accept(parser, T_PIPE))
	{
		right = parse_pipeline(parser);
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			return (NULL);
		new_node->type = PIPE;
		ast_attach_binary(new_node, left, right);
		return (new_node);
	}
	return (left);
}
t_node	*parse_command_rest(t_parser *parser, t_node *left)
{
	t_node	*right;
	t_node	*new_node;

	if (accept(parser, T_AND))
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			return (NULL);
		new_node->type = AND;
		right = parse_command_line(parser);
		ast_attach_binary(new_node, left, right);
		return (parse_command_rest(parser, new_node));
	}
	else if (accept(parser, T_OR))
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			return (NULL);
		new_node->type = OR;
		right = parse_command_line(parser);
		ast_attach_binary(new_node, left, right);
		return (parse_command_rest(parser, new_node));
	}
	return (left);
}

t_node	*parse_group(t_parser *parser)
{
	t_node	*new_node;

	if (!accept(parser, T_LPAREN))
		return (NULL);
	new_node = parse_command_line(parser);
	if (!expect(parser, T_RPAREN))
		return (NULL);
	return (new_node);
}

t_node	*parse_command_line(t_parser *parser)
{
	t_node	*left;

	if (accept(parser, T_LPAREN))
		left = parse_group(parser);
	else
		left = parse_pipeline(parser);
	return (parse_command_rest(parser, left));
}
