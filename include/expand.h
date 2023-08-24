/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:43:24 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/24 14:05:52 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"
# include "parser.h"

typedef enum e_expand_state
{
	EX_NONE = (1U << 0),
	EX_SINGLE_QUOTE = (1U << 1),
	EX_DOUBLE_QUOTE = (1U << 2),
}					t_expand_state;

typedef struct s_expand_str
{
	char			*result;
	size_t			result_size;
	char			*input;
	size_t			input_size;
	int				i;
	unsigned int	state;
}					t_expand_str;

typedef struct s_expand_var
{
	char			*name;
	char			*value;
	char			*end;
}					t_expand_var;

void				expand_tree(t_node *root, t_minishell *minishell);
void				free_expand_var(t_expand_var *var);
void				copy_and_increment(t_expand_str *expand);
void				change_state(unsigned int new_state, t_expand_str *expand);
void				handle_dollar(t_expand_str *expand, t_minishell *minishell);

#endif