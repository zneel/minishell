/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:42:28 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/02 18:15:22 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

char	*token_to_str(t_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_PIPE)
		return ("|");
	else if (type == T_AND)
		return ("&&");
	else if (type == T_OR)
		return ("||");
	else if (type == T_GREAT)
		return (">");
	else if (type == T_LESS)
		return ("<");
	else if (type == T_DLESS)
		return ("<<");
	else if (type == T_DGREAT)
		return (">>");
	else if (type == T_LPAREN)
		return ("(");
	else if (type == T_RPAREN)
		return (")");
	else if (type == T_NEWLINE)
		return ("newline");
	else if (type == T_EOF)
		return ("(null)");
	return ("T_UNKNOWN");
}
