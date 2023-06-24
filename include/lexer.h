/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/23 14:31:59 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stack.h>
# include <stdlib.h>

# define LPAREN '('
# define RPAREN ')'
# define QUOTE '\''
# define DQUOTE '\"'

/**
*  TOK_WORD = word (default)
*  TOK_PIPE = | (pipe)
*  TOK_SEMI = ; (semicolon)
*  TOK_AND = && (and)
*  TOK_OR = || (or)
*  TOK_RD_IN = < (redirection in)
*  TOK_RD_OUT = > (redirection out)
*  TOK_HEREDOC = << (here document in)
*  TOK_LPAREN = ( (parenthesis open)
*  TOK_RPAREN = ) (parenthesis close)
*  TOK_APPEND = >> (append)
*  TOK_END = \0	(end of line)
*  TOK_ERROR = error (error)
*/
typedef enum e_type
{
	TOK_WORD = 0,
	TOK_PIPE,
	TOK_SEMI,
	TOK_AND,
	TOK_OR,
	TOK_RD_IN,
	TOK_RD_OUT,
	TOK_HEREDOC,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_APPEND,
	TOK_END,
	TOK_ERROR,
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	size_t			len;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	char			*line;
	char			curr_char;
	size_t			curr_pos;
	size_t			read_pos;
	t_token			*tok_lst;
	size_t			tok_count;
}					t_lexer;

t_lexer				*lexer(char *line);
void				delete_lexer(t_lexer *lexer);
void				delete_token(t_token *token);
void				add_token(t_lexer *lexer, t_token *token);
t_token				*new_token(t_type type, char *value, size_t len);

void				debug_token(t_token *token);
void				debug_lexer(t_lexer *lexer);
void				debug_state(t_lexer *lexer);

#endif