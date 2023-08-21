/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:00:41 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 14:15:11 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	delete_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

void	delete_tokens(t_token *token)
{
	t_token	*curr;
	t_token	*tail;

	if (!token)
		return ;
	curr = token;
	while (curr)
	{
		tail = curr->next;
		delete_token(curr);
		curr = tail;
	}
}

void	delete_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	delete_tokens(lexer->token_lst);
	free(lexer);
}
