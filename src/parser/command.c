/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:11:07 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/24 19:06:11 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	is_redirect_token(t_parser *parser)
{
	return (peek(parser, T_DLESS) || peek(parser, T_DGREAT) || peek(parser,
			T_LESS) || peek(parser, T_GREAT));
}

int	count_args(t_parser *parser)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = parser->current_tok;
	while (curr && curr->type == T_WORD)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;
	int		i;

	node = new_node(COMMAND);
	if (!node)
		return (NULL);
	if (!peek(parser, T_WORD))
		return (node);
	node->data = malloc(sizeof(char *) * (count_args(parser) + 1));
	if (!node->data)
		return (NULL);
	i = 0;
	while (peek(parser, T_WORD))
	{
		node->data[i] = ft_strdup(parser->current_tok->value);
		i++;
		accept(parser, T_WORD);
	}
	node->data[i] = NULL;
	return (node);
}

t_node	*command(t_parser *parser)
{
	t_node	*cmd;
	t_node	*input;
	t_node	*output;
	t_bool	has_input;

	input = NULL;
	output = NULL;
	has_input = false;
	while (is_redirect_token(parser))
	{
		has_input = true;
		input = append_node_left(input, io_redirect(parser));
	}
	if (has_input && !input)
		return (NULL);
	cmd = simple_command(parser);
	if (!cmd)
		return (NULL);
	if (input)
		ast_attach_binary(cmd, input, NULL);
	while (is_redirect_token(parser))
		output = append_node_right(output, io_redirect(parser));
	if (output)
		ast_attach_binary(cmd, NULL, output);
	return (cmd);
}
