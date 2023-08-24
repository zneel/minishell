/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:14:19 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 13:16:08 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*group(t_parser *parser)
{
	t_node	*node;

	node = command_line(parser);
	if (!node)
		return (NULL);
	if (!accept(parser, T_RPAREN))
		return (ast_delete(node), NULL);
	return (node);
}
