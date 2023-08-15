/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:41 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/15 16:24:39 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_last(int pipefd[2][2])
{
	close_if(pipefd[0][0]);
	pipefd[0][0] = -1;
}

void	child_last(t_command *cmd, int pipefd[2][2], t_minishell *minishell)
{
	int	fdout;

	if (cmd->has_heredoc == false && cmd->has_infile == false)
	{
		close_if(pipefd[0][1]);
		dup2(pipefd[0][0], STDIN_FILENO);
		close_if(pipefd[0][0]);
	}
	else
		dup_for_in(cmd, minishell);
	if (cmd->has_append == false)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC, 0644);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND, 0644);
	if (fdout == -1)
		exit(free_and_msg("No such file or directory", cmd->file_out, minishell,
				cmd));
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

void	builtin_last(t_command *cmd, char **env, t_minishell *minishell)
{
	int	status;

	status = exec_builtin(cmd, minishell, false);
	exec_failed(cmd, env, minishell, status);
}

int	execute_last(t_command *cmd, t_minishell *minishell, int pipefd[2][2])
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		return (1);
	ft_lstadd_back(&minishell->pids, ft_lstnew(&pid));
	if (pid == 0)
		child_last(cmd, pipefd, minishell);
	else
		parent_last(pipefd);
	if (pid == 0)
	{
		env = convert_env(minishell->env);
		if (!env)
			exec_failed(cmd, env, minishell, 1);
		if (cmd->builtin)
			builtin_last(cmd, env, minishell);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			exec_failed(cmd, env, minishell, 1);
	}
	return (0);
}
