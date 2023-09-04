/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:03:52 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 13:07:30 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"
# include "stack.h"

typedef struct s_node	t_node;
/**
 *  T_WORD = word (default)
 *  T_PIPE = | (pipe)
 *  T_AND = && (and)
 *  T_OR = || (or)
 *  T_LESS = < (redirection in)
 *  T_GREAT = > (redirection out)
 *  T_DLESS = << (here document in)
 *  T_DGREAT = >> (append)
 *  T_LPAREN = ( (parenthesis open)
 *  T_RPAREN = ) (parenthesis close)
 *  T_NEWLINE = \n (newline)
 *  T_EOF = \0	(end of line)
 *  T_ERROR = error (error)
 */
typedef enum e_type
{
	T_START = 0,
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_LPAREN,
	T_RPAREN,
	T_NEWLINE,
	T_EOF,
}						t_type;

typedef struct s_token
{
	t_type				type;
	char				*value;
	size_t				len;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer
{
	char				*line;
	char				curr_char;
	size_t				curr_pos;
	size_t				read_pos;
	size_t				line_len;
	t_token				*token_lst;
	size_t				token_count;
}						t_lexer;

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
	t_list				*redirs;
	t_list				*args;
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

typedef struct s_redirect
{
	t_node_type			type;
	char				*file;
}						t_redirect;

typedef struct s_kv
{
	char				*key;
	char				*value;
	struct s_kv			*next;
}						t_kv;

typedef struct s_minishell
{
	t_kv				*env;
	t_list				*pids;
	t_node				*root;
	int					last_status;
	int					m_fd[2];
	int					shlevel;
}						t_minishell;

#endif