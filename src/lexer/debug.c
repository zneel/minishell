/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:42:28 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 15:51:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

char	*token_to_tstr(t_type type)
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
	else if (type == T_NEWLINE)
		return ("T_NEWLINE");
	else if (type == T_EOF)
		return ("T_EOF");
	else
		return ("T_UNKNOWN");
}

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
	else
		return ("T_UNKNOWN");
}

void	debug_token(t_token *token)
{
	printf("token->type=%s\n", token_to_tstr(token->type));
	printf("token->value=%s\n", token->value);
	printf("token->len=%lu\n", token->len);
}

void	debug_lexer(t_lexer *lexer)
{
	t_token	*curr;

	curr = lexer->token_lst;
	printf("====================================\n");
	while (curr)
	{
		debug_token(curr);
		printf("lexer->T_count=%lu\n", lexer->token_count);
		printf("====================================\n");
		curr = curr->next;
	}
}
