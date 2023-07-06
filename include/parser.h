/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:25:00 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 09:49:22 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
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
	WORD,
}						t_node_type;

struct					s_node
{
	t_node_type			*type;
	char				*value;
	t_node				*left;
	t_node				*right;
};

typedef struct s_parser
{
	t_token				*current_tok;
	long				parse_state;
	t_stack				*parse_stack;
	t_node				*root;
}						t_parser;

#endif