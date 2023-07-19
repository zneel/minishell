/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:25:00 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/19 13:03:20 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

typedef struct s_node t_node;

typedef enum e_node_type
{
	PIPE,
	AND,
	OR,
	LESS,
	GREAT,
	DGREAT,
	COMMAND,
	L_PAREN,
	R_PAREN,
}						t_node_type;

struct s_node
{
	t_node_type			type;
	char				*raw_command;
	t_node				*left;
	t_node				*right;
	t_node				*parent;
};

#endif