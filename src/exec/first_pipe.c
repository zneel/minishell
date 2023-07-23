/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:37 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 20:08:29 by mhoyer           ###   ########.fr       */
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

	if (cmd->has_heredoc == 0)
		fdin = open(cmd->file_in, O_RDONLY);
	else
		fdin = open(file_heredoc, O_RDONLY);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == 0)
			exit(msg_error("No such file or directory", cmd->file_in));
		else
			exit(msg_error("No such file or directory", file_heredoc));
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	close_if(pipefd[1][0]);
	dup2(pipefd[1][1], STDOUT_FILENO);
	close_if(pipefd[1][1]);
}

int	execute_first(t_command *cmd, t_minishell *minishell, int pipefd[2][2])
{
	pid_t	pid;
	char	**env;

	if (cmd->has_heredoc)
		here_doc(cmd->file_in);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_first(cmd, pipefd);
	else
		parent_first(pipefd);
	if (pid == 0)
	{
		env = convert_env(minishell->env);
		if (!env)
			return (1);
		if ((cmd->command == NULL || cmd->command[0] == NULL) || (execve(cmd->command[0], cmd->command, env) == -1))
		{
			msg_error("Cmd not found", cmd->command[0]);
			free_cmd(cmd);
			free_mat(env);
			free_minishell(minishell);
			exit(1);
		}
	}
	return (0);
}
