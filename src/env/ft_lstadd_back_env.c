/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:40:06 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 12:50:38 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_kv **lst, t_kv *new_node)
{
	t_kv	*current;
	t_kv	*tail;

	if (!*lst)
		*lst = new_node;
	else
	{
		current = *lst;
		tail = NULL;
		while (current)
		{
			tail = current;
			current = current->next;
		}
		tail->next = new_node;
	}
}
