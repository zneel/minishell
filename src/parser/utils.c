/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:00:29 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/02 18:14:09 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>

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
