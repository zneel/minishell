/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:14:34 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/29 14:17:26 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	peek_redirect(t_parser *parser)
{
	if (peek(parser, T_LESS) || peek(parser, T_GREAT) || peek(parser, T_DGREAT)
		|| peek(parser, T_DLESS))
		return (true);
	return (false);
}

t_bool	accept_redirect(t_parser *parser)
{
	if (accept(parser, T_LESS) || accept(parser, T_GREAT) || accept(parser,
			T_DGREAT) || accept(parser, T_DLESS))
		return (true);
	return (false);
}

void	io_redirect(t_parser *parser, t_node *cmd)
{
	t_bool		accepted;
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return ;
	if (!peek_redirect(parser))
		return ;
	redir->type = lexer_to_node(parser->current_tok->type);
	accepted = accept_redirect(parser);
	if (!peek(parser, T_WORD) || !accepted)
	{
		free(redir);
		return ;
	}
	redir->file = ft_strdup(parser->current_tok->value);
	ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	accept(parser, T_WORD);
}
