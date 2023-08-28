/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:00:35 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/28 13:01:37 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	accept(t_parser *parser, t_type type)
{
	if (type == parser->current_tok->type)
	{
		parser->current_tok = parser->current_tok->next;
		return (true);
	}
	return (false);
}

t_bool	peek(t_parser *parser, t_type type)
{
	if (type == parser->current_tok->type)
		return (true);
	return (false);
}

t_bool	expect(t_parser *parser, t_type type)
{
	if (accept(parser, type))
		return (true);
	return (false);
}

t_bool	peek_next(t_parser *parser, t_type type)
{
	if (parser && parser->current_tok && !parser->current_tok->next)
		return (false);
	if (type == parser->current_tok->next->type)
		return (true);
	return (false);
}
