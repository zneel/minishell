/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:14:34 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 13:16:10 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
