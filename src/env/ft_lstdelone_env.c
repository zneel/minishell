/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:39:13 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/29 11:35:02 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_env(t_kv *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->key);
		del(lst->value);
		free(lst);
	}
}
