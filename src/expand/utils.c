/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:03:38 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/30 16:17:25 by ebouvier         ###   ########.fr       */
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

void	free_redir(void *redir)
{
	t_redirect	*tmp;

	tmp = (t_redirect *)redir;
	free(tmp->file);
	free(tmp);
}

t_list	*delete_expand_node(t_list **lst, t_list *to_delete, t_bool is_redir)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	prev = NULL;
	while (curr && curr != to_delete)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*lst = to_delete->next;
	else
		prev->next = to_delete->next;
	if (is_redir)
		ft_lstdelone(to_delete, free_redir);
	else
		ft_lstdelone(to_delete, free);
	if (!prev)
		return (*lst);
	return (prev->next);
}
