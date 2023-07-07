/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:50:25 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 12:54:29 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_env(t_kv **lst, void (*del)(void *))
{
	t_kv	*current;
	t_kv	*tail;

	if (!del || !lst)
		return ;
	current = *lst;
	tail = NULL;
	while (current)
	{
		del(current->key);
		del(current->value);
		tail = current;
		current = current->next;
		free(tail);
	}
	*lst = NULL;
}
