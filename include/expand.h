/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:43:24 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/27 16:45:47 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "parser.h"

typedef enum e_expand_state
{
	NONE = (1U << 0),
	SINGLE_QUOTE = (1U << 1),
	DOUBLE_QUOTE = (1U << 2),
}		t_expand_state;

void	expand_tree(t_node *root);

#endif