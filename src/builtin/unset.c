/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:32:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/01 11:30:46 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_bool	is_same(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

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
	if (!cmd->command || !cmd->command[0] || !cmd->command[1])
		return (1);
	while (cmd->command[i])
	{
		delete_node(&minishell->env, cmd->command[i]);
		i++;
	}
	return (0);
}
