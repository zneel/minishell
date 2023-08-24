/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:14:34 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 21:32:26 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*io_redirect(t_parser *parser)
{
	t_node	*node;

	node = NULL;
	if (accept(parser, T_LESS))
		node = new_node(LESS);
	else if (accept(parser, T_GREAT))
		node = new_node(GREAT);
	else if (accept(parser, T_DGREAT))
		node = new_node(DGREAT);
	else if (accept(parser, T_DLESS))
		node = new_node(HERE_DOC);
	if (!node)
		return (NULL);
	if (!peek(parser, T_WORD))
		return (free(node), NULL);
	node->data = malloc(sizeof(char *) * 2);
	if (!node->data)
		return (free(node), NULL);
	node->data[0] = ft_strdup(parser->current_tok->value);
	node->data[1] = NULL;
	accept(parser, T_WORD);
	return (node);
}
