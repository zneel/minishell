/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:21:54 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 13:29:14 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_kv *lst)
{
	int		size;
	t_kv	*current;

	size = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		++size;
	}
	return (size);
}
