/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:58 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 00:33:42 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*lex(char *line)
{
	ft_printf("lexed=%s\n", line);
	return (NULL);
}

void	delete_lexer(t_lexer *lexer)
{
    t_token *curr;
    t_token *tail;

    curr = lexer->tok_lst;
    while (curr)
    {
        tail = curr;
        curr = curr->next; 
        free(tail->value);
        free(tail);
    }
}