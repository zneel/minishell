/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:20 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/30 17:07:37 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ft_printf.h"
# include "libft.h"
# include "lists.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>

# define LPAREN '('
# define RPAREN ')'
# define QUOTE '\''
# define DQUOTE '\"'

t_lexer	*lexer(char *line);
void	delete_lexer(t_lexer *lexer);
void	delete_token(t_token *token);
void	add_token(t_lexer *lexer, t_token *token);
t_token	*new_token(t_type type, char *value);
t_token	*next_token(t_lexer *lexer);
void	advance(t_lexer *lexer);
void	advance_twice(t_lexer *lexer);
char	lexer_peek(t_lexer *lexer);
char	*handle_word(t_lexer *lexer);

void	debug_token(t_token *token);
void	debug_lexer(t_lexer *lexer);
char	*token_to_str(t_type type);

t_bool	is_special_char(t_lexer *lexer);
void	escape_quotes(t_lexer *lexer);
char	*handle_word(t_lexer *lexer);
t_bool	validate(t_lexer *lexer);

#endif