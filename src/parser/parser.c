/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:05:49 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 10:49:17 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	shift(t_parser *parser)
{
	if (parser->current_tok->type == T_WORD)
		stack_push(&parser->parse_stack, parser->current_tok);
}

void	set_parser_error(t_parser *parser, t_error error)
{
	parser->error |= error;
}

void	reduce(t_parser *parser)
{
	t_token	*top;
	t_list	*new;

	top = stack_peek(parser->parse_stack);
	if (parser->current_tok->type == T_PIPE
		|| parser->current_tok->type == T_AND
		|| parser->current_tok->type == T_OR
		|| parser->current_tok->type == T_DGREAT
		|| parser->current_tok->type == T_DLESS
		|| parser->current_tok->type == T_GREAT
		|| parser->current_tok->type == T_LESS)
		while (top)
		{
			top = stack_peek(parser->parse_stack);
			new = ft_lstnew(top->value);
			if (!new)
				return (set_parser_error(parser, FATAL));
			ft_lstadd_back(&parser->root->raw_command, new);
			stack_pop(&parser->parse_stack, (void (*)(void *))delete_token);
		}
}

void	consume_token(t_parser *parser, t_lexer *lexer)
{
	if (lexer && lexer->token_lst)
	{
		if (lexer->token_lst->next)
			parser->current_tok = lexer->token_lst;
	}
}

int	init_parser(t_parser *parser)
{
	parser->current_tok = NULL;
	parser->parse_stack = malloc(sizeof(t_stack));
	if (!parser->parse_stack)
		return (0);
	parser->root = NULL;
	parser->parse_state = 0;
	parser->error = NO_ERROR;
	return (1);
}

t_node	*parse(t_lexer *lexer)
{
	t_parser	parser;

	if (!lexer && !init_parser(&parser))
		return (NULL);
	consume_token(&parser, lexer);
	return (parser.root);
}
