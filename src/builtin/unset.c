/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:32:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 16:18:05 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	delete_node(t_kv **head, char *env)
{
	t_kv	*prev;
	t_kv	*tmp;

	tmp = *head;
	prev = NULL;
	if (tmp && is_same(tmp->key, env))
	{
		*head = tmp->next;
		ft_lstdelone_env(tmp, free);
		return ;
	}
	while (tmp && !is_same(tmp->key, env))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	ft_lstdelone_env(tmp, free);
}

int	unset(t_command *cmd, t_minishell *minishell)
{
	int	i;

	i = 1;
	if (!cmd->command || !cmd->command[0])
		return (1);
	if (!cmd->command[1])
		return (0);
	while (cmd->command[i])
	{
		delete_node(&minishell->env, cmd->command[i]);
		i++;
	}
	return (0);
}
