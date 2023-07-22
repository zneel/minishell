/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:52:56 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 09:53:16 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_command(t_command *cmd, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (execve(cmd->command[0], cmd->command, env) == -1)
			printf("exitcmd");
	}
}
