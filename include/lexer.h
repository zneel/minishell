/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 00:33:43 by ebouvier         ###   ########.fr       */
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
	TOK_WORD = (1U << 0),
	TOK_PIPE = (1U << 1),
	TOK_AMP = (1U << 2),
	TOK_QUOTE = (1U << 3),
	TOK_DQUOTE = (1U << 4),
	TOK_SEMI = (1U << 5),
	TOK_GT = (1U << 6),
	TOK_LT = (1U << 7),
	TOK_DGT = (1U << 8),
	TOK_DLT = (1U << 9),
	TOK_DAMP = (1U << 10),
	TOK_DPIPE = (1U << 11),
	TOK_DOLLAR = (1U << 12),
	TOK_ASTERISK = (1U << 13),
};

enum				e_state
{
	STATE_DEFAULT = (1U << 0),
	STATE_IN_QUOTE = (1U << 1),
	STATE_IN_DQUOTE = (1U << 2),
	STATE_IN_ASTERISK = (1U << 3),
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

t_token				*lex(char *line);
void				delete_lexer(t_lexer *lexer);

#endif