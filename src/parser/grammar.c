/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:17:18 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/14 14:45:28 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>

t_node		*command_line(t_parser *parser);

t_node_type	lexer_to_node(t_type type)
{
	if (type == T_LESS)
		return (LESS);
	else if (type == T_GREAT)
		return (GREAT);
	else if (type == T_DGREAT)
		return (DGREAT);
	else if (type == T_DLESS)
		return (HERE_DOC);
	else if (type == T_PIPE)
		return (PIPE);
	else if (type == T_AND)
		return (AND);
	else if (type == T_OR)
		return (OR);
	else if (type == T_WORD)
		return (COMMAND);
	return (UNKNOWN);
}

t_node	*new_node(t_node_type type, char *data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

t_node	*io_redirect(t_parser *parser)
{
	t_node	*node;

	node = NULL;
	if (accept(parser, T_LESS))
		node = new_node(LESS, NULL);
	else if (accept(parser, T_GREAT))
		node = new_node(GREAT, NULL);
	else if (accept(parser, T_DGREAT))
		node = new_node(DGREAT, NULL);
	else if (accept(parser, T_DLESS))
		node = new_node(HERE_DOC, NULL);
	if (!node)
		return (NULL);
	if (!peek(parser, T_WORD))
		return (free(node), NULL);
	node->data = ft_strdup(parser->current_tok->value);
	accept(parser, T_WORD);
	return (node);
}

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;
	char	*tmp;
	char	*new_word;
	char	*joined;

	if (!peek(parser, T_WORD))
		return (NULL);
	node = new_node(COMMAND, ft_strdup(parser->current_tok->value));
	if (!node)
		return (NULL);
	accept(parser, T_WORD);
	while (peek(parser, T_WORD))
	{
		tmp = node->data;
		new_word = ft_strjoin(" ", parser->current_tok->value);
		joined = ft_strjoin(tmp, new_word);
		free(tmp);
		free(new_word);
		node->data = joined;
		accept(parser, T_WORD);
	}
	return (node);
}

t_node	*append_node_left(t_node *head, t_node *append)
{
	t_node	*tmp;

	tmp = head;
	if (!head)
		return (append);
	while (tmp->left)
		tmp = tmp->left;
	tmp->left = append;
	return (head);
}

t_node	*append_node_right(t_node *head, t_node *append)
{
	t_node	*tmp;

	tmp = head;
	if (!head)
		return (append);
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = append;
	return (head);
}

t_node	*command(t_parser *parser)
{
	t_node	*cmd;
	t_node	*input;
	t_node	*output;

	input = NULL;
	output = NULL;
	while (peek(parser, T_LESS) || peek(parser, T_DLESS))
		input = append_node_left(input, io_redirect(parser));
	cmd = simple_command(parser);
	if (!cmd)
		return (NULL);
	if (input)
		ast_attach_binary(cmd, input, NULL);
	while (peek(parser, T_GREAT) || peek(parser, T_DGREAT))
		output = append_node_right(output, io_redirect(parser));
	if (output)
		ast_attach_binary(cmd, NULL, output);
	return (cmd);
}

void	free_stack(t_stack *stack)
{
	free(stack->content);
	free(stack);
}

t_node	*group(t_parser *parser)
{
	t_node	*node;
	char	*top;

	node = command_line(parser);
	if (!node)
		return (NULL);
	top = stack_peek(parser->parse_stack);
	if (!accept(parser, T_RPAREN))
		return (ast_delete(node), NULL);
	if (top && *top == '(')
		stack_pop(&parser->parse_stack, (void *)free_stack);
	return (node);
}

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
		pipe_node = new_node(PIPE, NULL);
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
		stack_push(&parser->parse_stack, ft_strdup("("));
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
		logical_node = new_node(lexer_to_node(parser->current_tok->type),
								NULL);
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

void	delete_parse(t_node *root, t_parser *parser)
{
	ast_delete(root);
	stack_delete(&parser->parse_stack, (void *)free_stack);
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
		delete_parse(root, parser);
		return (NULL);
	}
	if (!stack_is_empty(parser->parse_stack))
	{
		ft_dprintf(2, "minishell: unclosed parenthesis\n");
		delete_parse(root, parser);
		return (NULL);
	}
	if (!root)
		return (NULL);
	return (root);
}
