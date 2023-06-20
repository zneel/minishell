/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:42:28 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/20 11:45:07 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "libft.h"

char	*token_to_str(t_type type)
{
	if (type == TOK_WORD)
		return ("TOK_WORD");
	else if (type == TOK_PIPE)
		return ("TOK_PIPE");
	else if (type == TOK_SEMI)
		return ("TOK_SEMI");
	else if (type == TOK_AND)
		return ("TOK_AND");
	else if (type == TOK_OR)
		return ("TOK_OR");
	else if (type == TOK_RD_IN)
		return ("TOK_RD_IN");
	else if (type == TOK_RD_OUT)
		return ("TOK_RD_OUT");
	else if (type == TOK_HEREDOC)
		return ("TOK_HEREDOC");
	else if (type == TOK_LPAREN)
		return ("TOK_LPAREN");
	else if (type == TOK_RPAREN)
		return ("TOK_RPAREN");
	else if (type == TOK_APPEND)
		return ("TOK_APPEND");
	else if (type == TOK_END)
		return ("TOK_END");
	else if (type == TOK_ERROR)
		return ("TOK_ERROR");
	else
		return ("TOK_UNKNOWN");
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

	curr = lexer->tok_lst;
	ft_printf("====================================\n");
	while (curr)
	{
		debug_token(curr);
		ft_printf("lexer->tok_count=%d\n", lexer->tok_count);
		ft_printf("====================================\n");
		curr = curr->next;
	}
}
