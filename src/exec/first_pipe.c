/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:37 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/29 13:23:07 by mhoyer           ###   ########.fr       */
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
	if (dup_in(cmd))
		exit (1);
	if (cmd->mode & M_NO_MODE)
	{
		close_if(pipefd[1][0]);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_if(pipefd[1][1]);
	}
	else
	{
		if (dup_out(cmd))
			exit (1);
	}
}

void	builtin_first(t_command *cmd, char **env, t_minishell *minishell)
{
	int	status;

	status = exec_builtin(cmd, minishell, false);
	exec_failed(cmd, env, minishell, status);
}

int	execute_first(t_command *cmd, t_minishell *minishell, int pipefd[2][2])
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		return (1);
	ft_lstadd_back(&minishell->pids, ft_lstnew(&pid));
	if (pid == 0)
		child_first(cmd, pipefd);
	else
		parent_first(pipefd);
	if (pid == 0)
	{
		env = convert_env(minishell->env);
		if (!env && !cmd->has_path && !cmd->builtin)
			exec_failed(cmd, env, minishell, 1);
		if (cmd->builtin)
			builtin_first(cmd, env, minishell);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			exec_failed(cmd, env, minishell, 1);
	}
	return (0);
}
