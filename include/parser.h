/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:25:00 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/18 13:19:32 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"
# include "lists.h"
# include "stack.h"

typedef struct s_node	t_node;

typedef enum e_node_type
{
	PIPE,
	AND,
	OR,
	LESS,
	GREAT,
	DGREAT,
	COMMAND,
	HERE_DOC,
	UNKNOWN,
}						t_node_type;

struct					s_node
{
	t_node_type			type;
	char				*data;
	t_node				*left;
	t_node				*right;
	t_node				*parent;
};

typedef struct s_parser
{
	t_token				*current_tok;
	long				parse_state;
	t_stack				*parse_stack;
	t_lexer				*lexer;
}						t_parser;

/*
PARSER
*/
t_bool					accept(t_parser *parser, t_type type);
t_bool					expect(t_parser *parser, t_type type);
t_bool					peek(t_parser *parser, t_type type);

/*
GRAMMAR
*/
t_node					*command_line(t_parser *parser);
t_node					*simple_command(t_parser *parser);
t_node					*command(t_parser *parser);
t_node					*io_redirect(t_parser *parser);
t_node					*group(t_parser *parser);
t_node					*parse_grammar(t_parser *parser);
t_node					*parse(t_lexer *lexer);

/*
AST
*/
void					ast_delete(t_node *node);
void					ast_attach_binary(t_node *root, t_node *left,
							t_node *right);
t_node					*new_node(t_node_type type, char *data);
t_node					*append_node_left(t_node *head, t_node *append);
t_node					*append_node_right(t_node *head, t_node *append);

/*
UTILS
*/
void					pretty_print_ast(t_node *node, char *prefix);
char					*node_type_to_str(t_node_type type);
t_node_type				lexer_to_node(t_type type);

#endif