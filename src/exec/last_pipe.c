/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:41 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 17:15:05 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_last(int pipefd[2][2])
{
	close_if(pipefd[0][0]);
	pipefd[0][0] = -1;
}

void	child_last(t_command *cmd, int pipefd[2][2])
{
	int	fdout;

	close_if(pipefd[0][1]);
	dup2(pipefd[0][0], STDIN_FILENO);
	close_if(pipefd[0][0]);
	fdout = open(cmd->file_out, O_WRONLY);
	dup2(fdout, 1);
	close(fdout);
}

int	execute_last(t_command *cmd, char **env, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_last(cmd, pipefd);
	else
		parent_last(pipefd);
	if (pid == 0)
	{
		if (execve(cmd->command[0], cmd->command, env) == -1)
		{
			exit(msg_error("Cmd not found"));
		}
	}
	return (0);
}
