/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:32:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/26 22:09:22 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset(t_command *cmd, t_minishell *minishell)
{
	int		i;
	t_kv	*parc;

	i = 0;
	if (!cmd->command || !cmd->command[0] || !cmd->command[1])
		return (1);
	while (cmd->command[++i])
	{
		parc = minishell->env;
		while (parc)
		{
			if (get_env(*minishell, cmd->command[i]))
			{
				ft_lstdelone_env(minishell->env, parc, free);
				parc = NULL;
			}
			if (parc)
				parc = parc->next;
		}
	}
	return (0);
}
