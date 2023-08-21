/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:36 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 15:38:26 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "stack.h"

t_bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

t_bool	quotes_valid(char *line)
{
	t_stack	*stack;
	int		i;

	i = -1;
	stack = NULL;
	while (line[++i])
	{
		if (line[i] == '\'' && stack_peek(stack)
			&& *(char *)stack_peek(stack) == '\'')
			stack_pop(&stack, free);
		else if (line[i] == '\"' && stack_peek(stack)
			&& *(char *)stack_peek(stack) == '\"')
			stack_pop(&stack, free);
		else if (is_quote(line[i]) && stack_is_empty(stack))
			stack_push(&stack, &line[i]);
	}
	if (!stack_is_empty(stack))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error unclosed quote: `%c\'\n",
			*(char *)stack_peek(stack));
		return (stack_delete(stack, NULL), false);
	}
	return (stack_is_empty(stack));
}

t_bool	validate(t_lexer *lexer)
{
	if (!lexer)
		return (false);
	if (!lexer->line)
		return (false);
	if (!quotes_valid(lexer->line))
		return (false);
	return (true);
}
