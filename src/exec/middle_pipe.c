/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:39 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 17:14:57 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_middle(int pipefd[2][2])
{
	close_if(pipefd[0][0]);
	pipefd[0][0] = pipefd[1][0];
	pipefd[1][0] = -1;
	close_if(pipefd[1][1]);
}

void	child_middle(int pipefd[2][2])
{
	close_if(pipefd[0][1]);
	dup2(pipefd[0][0], STDIN_FILENO);
	close_if(pipefd[0][0]);
	close_if(pipefd[1][0]);
	dup2(pipefd[1][1], STDOUT_FILENO);
	close_if(pipefd[1][1]);
}

int	execute_middle(t_command *cmd, char **env, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_middle(pipefd);
	else
		parent_middle(pipefd);
	if (pid == 0)
	{
		if (execve(cmd->command[0], cmd->command, env) == -1)
		{
			exit(msg_error("Cmd not found"));
		}
	}
	return (0);
}
