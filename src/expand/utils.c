/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:03:38 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/30 12:56:26 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	free_expand_var(t_expand_var *var)
{
	free(var->name);
	free(var);
}

void	copy_and_increment(t_expand_str *expand)
{
	expand->result = ft_realloc(expand->result, expand->result_size + 1);
	*(expand->result + expand->i++) = *expand->input;
	expand->result_size++;
	expand->input++;
}

void	change_state(unsigned int new_state, t_expand_str *expand)
{
	expand->state ^= new_state;
	expand->input++;
}

t_list	*delete_expand_node(t_list **lst, t_list *to_delete)
{
	t_list	*tmp;

	tmp = to_delete->next;
	ft_lstdelone(to_delete, free);
	if (to_delete == *lst)
		*lst = tmp;
	return (tmp);
}
