/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:11:07 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/01 17:48:09 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	is_redirect_token(t_parser *parser)
{
	t_bool	has_redirect;
	t_bool	has_word_next;

	has_redirect = false;
	if (peek(parser, T_DLESS) || peek(parser, T_DGREAT) || peek(parser, T_LESS)
		|| peek(parser, T_GREAT))
		has_redirect = true;
	has_word_next = peek_next(parser, T_WORD);
	return (has_redirect && has_word_next);
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

void	simple_command(t_parser *parser, t_node *cmd)
{
	while (peek(parser, T_WORD))
	{
		ft_lstadd_back(&cmd->args,
			ft_lstnew(ft_strdup(parser->current_tok->value)));
		accept(parser, T_WORD);
	}
}

t_node	*command(t_parser *parser)
{
	t_node	*cmd;

	cmd = new_node(COMMAND);
	if (!cmd)
		return (NULL);
	while (peek(parser, T_WORD) || is_redirect_token(parser))
	{
		simple_command(parser, cmd);
		while (is_redirect_token(parser))
			io_redirect(parser, cmd);
	}
	if (!cmd->args && !cmd->redirs)
		return (ast_delete(cmd), NULL);
	return (cmd);
}
