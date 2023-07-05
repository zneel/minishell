/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:16:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/05 16:49:58 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lexer.h"
#include "libft.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (!value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->len = ft_strlen(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_lexer *lexer, t_token *token)
{
	t_token	*curr;

	ft_printf("adding token:%s\n", token->value);
	curr = lexer->token_lst;
	if (!curr)
		lexer->token_lst = token;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = token;
	}
	lexer->token_count++;
}
