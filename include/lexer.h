/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/21 15:42:30 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ft_printf.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>

# define LPAREN '('
# define RPAREN ')'
# define QUOTE '\''
# define DQUOTE '\"'

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
 *  T_END = \0	(end of line)
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
	T_EOF,
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
	size_t			line_len;
	t_token			*token_lst;
	size_t			token_count;
}					t_lexer;

t_lexer				*lexer(char *line);
void				delete_lexer(t_lexer *lexer);
void				delete_token(t_token *token);
void				add_token(t_lexer *lexer, t_token *token);
t_token				*new_token(t_type type, char *value);
t_token				*next_token(t_lexer *lexer);
void				advance(t_lexer *lexer);
void				advance_twice(t_lexer *lexer);
char				lexer_peek(t_lexer *lexer);
char				*handle_word(t_lexer *lexer);

void				debug_token(t_token *token);
void				debug_lexer(t_lexer *lexer);
char				*token_to_str(t_type type);

t_bool				is_special_char(t_lexer *lexer);
void				escape_quotes(t_lexer *lexer);
char				*handle_word(t_lexer *lexer);
t_bool				validate(t_lexer *lexer);

#endif