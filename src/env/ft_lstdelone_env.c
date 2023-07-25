/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:39:13 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/25 12:02:26 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_env(t_kv *mem, t_kv *lst, void (*del)(void *))
{
	while (mem && ft_strncmp(mem->next->key, lst->key,
			ft_strlen(lst->key)) != 0)
		mem = mem->next;
	mem->next = lst->next;
	if (lst && del)
	{
		del(lst->key);
		del(lst->value);
		free(lst);
	}
}
