/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:16:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/24 13:42:15 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	if (value)
		token->len = ft_strlen(value);
	else
		token->len = 0;
	token->next = NULL;
	return (token);
}

void	add_token(t_lexer *lexer, t_token *token)
{
	t_token	*curr;

	if (!token->value)
		printf("ADD TOKEN TYPE=%s VALUE=NULL\n", token_to_str(token->type));
	else
		printf("ADD TOKEN TYPE=%s VALUE=%s\n", token_to_str(token->type),
				token->value);
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
