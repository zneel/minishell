/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:37 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 17:14:46 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_first(int pipefd[2][2])
{
	close_if(pipefd[0][0]);
	pipefd[0][0] = pipefd[1][0];
	pipefd[1][0] = -1;
	close_if(pipefd[1][1]);
}

void	child_first(t_command *cmd, int pipefd[2][2])
{
	int	fdin;

	fdin = open(cmd->file_in, O_RDONLY);
	if (fdin == -1)
		exit(msg_error("Infile not found"));
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	close_if(pipefd[1][0]);
	dup2(pipefd[1][1], STDOUT_FILENO);
	close_if(pipefd[1][1]);
}

int	execute_first(t_command *cmd, char **env, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_first(cmd, pipefd);
	else
		parent_first(pipefd);
	if (pid == 0)
	{
		if (execve(cmd->command[0], cmd->command, env) == -1)
		{
			exit(msg_error("Cmd not found"));
		}
	}
	return (0);
}
