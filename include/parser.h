/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:25:00 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/24 19:02:01 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "lists.h"
# include "stack.h"

typedef struct s_node	t_node;

typedef enum e_error
{
	NO_ERROR = (1U << 0),
	SYNTAX_ERROR = (1U << 1),
	FATAL_ERROR = (1U << 2),
}						t_error;

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
	t_node				*root;
	t_error				error;
}						t_parser;

int						accept(t_parser *parser, t_type type);
int						expect(t_parser *parser, t_type type);
int						peek(t_parser *parser, t_type type);

void					ast_attach_binary(t_node *root, t_node *left,
							t_node *right);

t_node					*parse_here_end(t_parser *parser);
t_node					*parse_filename(t_parser *parser);
t_node					*parse_io_here(t_parser *parser);
t_node					*parse_io_file(t_parser *parser);
t_node					*parse_io_redirect(t_parser *parser);
t_node					*parse_suffix(t_parser *parser);
t_node					*parse_cmd_word(t_parser *parser);
t_node					*parse_prefix(t_parser *parser);
t_node					*parse_command(t_parser *parser);
t_node					*parse_pipeline_rest(t_parser *parser);
t_node					*parse_pipeline(t_parser *parser);
t_node					*parse_command_rest(t_parser *parser, t_node *left);
t_node					*parse_command_line(t_parser *parser);
t_node					*parse_group(t_parser *parser);

#endif