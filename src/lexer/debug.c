/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:42:28 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/05 16:50:23 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "libft.h"

char	*token_to_str(t_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_AND)
		return ("T_AND");
	else if (type == T_OR)
		return ("T_OR");
	else if (type == T_GREAT)
		return ("T_GREAT");
	else if (type == T_LESS)
		return ("T_LESS");
	else if (type == T_DLESS)
		return ("T_DLESS");
	else if (type == T_DGREAT)
		return ("T_DGREAT");
	else if (type == T_LPAREN)
		return ("T_LPAREN");
	else if (type == T_RPAREN)
		return ("T_RPAREN");
	else if (type == T_END)
		return ("T_END");
	else if (type == T_ERROR)
		return ("T_ERROR");
	else
		return ("T_UNKNOWN");
}

void	debug_token(t_token *token)
{
	ft_printf("token->type=%s\n", token_to_str(token->type));
	ft_printf("token->value=%s\n", token->value);
	ft_printf("token->len=%d\n", token->len);
}

void	debug_lexer(t_lexer *lexer)
{
	t_token	*curr;

	curr = lexer->token_lst;
	ft_printf("====================================\n");
	while (curr)
	{
		debug_token(curr);
		ft_printf("lexer->T_count=%d\n", lexer->token_count);
		ft_printf("====================================\n");
		curr = curr->next;
	}
}
