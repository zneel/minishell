/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 00:47:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/**
*  TOK_WORD = word
*  TOK_PIPE = |
*  TOK_AMP = &
*  TOK_QUOTE = '
*  TOK_DQUOTE = "
*  TOK_SEMI = ;
*  TOK_GT = >
*  TOK_LT = <
*  TOK_DGT = >>
*  TOK_DLT = <<
*  TOK_DAMP = &&
*  TOK_DPIPE = ||
*  TOK_DOLLAR = $
*  TOK_ASTERISK = *
*/
enum				e_token
{
	TOK_WORD,
	TOK_PIPE,
	TOK_AMP,
	TOK_QUOTE,
	TOK_DQUOTE,
	TOK_SEMI,
	TOK_GT,
	TOK_LT,
	TOK_DGT,
	TOK_DLT,
	TOK_DAMP,
	TOK_DPIPE,
	TOK_DOLLAR,
	TOK_ASTERISK,
};

enum				e_state
{
	STATE_DEFAULT,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_IN_ASTERISK,
};

typedef struct s_token
{
	enum e_token	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	t_token			*tok_lst;
	enum e_state	state;
}					t_lexer;

t_token				*lexer(char *line);
void				delete_lexer(t_lexer *lexer);

/**
 * debug functions 
 */

void				debug_lexer(t_lexer *lexer);

#endif