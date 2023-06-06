/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:58 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 00:47:26 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_lexer	*init_lexer(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->state = STATE_DEFAULT;
	lexer->tok_lst = NULL;
	return (lexer);
}

t_token	*lexer(char *line)
{
	t_lexer	*lexer;

	lexer = init_lexer();
	ft_printf("lexed=%s\n", line);
	debug_lexer(lexer);
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