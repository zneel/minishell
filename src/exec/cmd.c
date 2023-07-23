/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:52:56 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 09:18:22 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_command(t_command *cmd, t_minishell *minishell)
{
	pid_t pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		env = convert_env(minishell->env);
		if (!env)
			exit (1);
		if ((cmd->command == NULL || cmd->command[0] == NULL) || (execve(cmd->command[0], cmd->command, env) == -1))
		{
			free_cmd(cmd);
			free_mat(env);
			free_minishell(minishell);
			exit(msg_error("Cmd not found"));
		}
	}
}
