/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:11:07 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 13:16:02 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
