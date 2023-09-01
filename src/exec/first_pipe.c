/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:37 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 17:01:05 by ebouvier         ###   ########.fr       */
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

void	child_first(t_command *cmd, int pipefd[2][2], t_minishell *ms)
{
	if (!cmd->has_good_file)
		close_all_pipe_free(pipefd, ms, cmd);
	if (dup_in(cmd))
		close_all_pipe_free(pipefd, ms, cmd);
	if (cmd->mode & (M_APPEND | M_OUT))
	{
		close_if(pipefd[1][0]);
		close_if(pipefd[1][1]);
		if (dup_out(cmd))
			close_all_pipe_free(pipefd, ms, cmd);
	}
	else
	{
		close_if(pipefd[1][0]);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_if(pipefd[1][1]);
	}
	close_if(ms->m_fd[0]);
	close_if(ms->m_fd[1]);
}

int	execute_first(t_command *cmd, t_minishell *minishell, int pipefd[2][2])
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid != 0)
		ft_lstadd_back(&minishell->pids, ft_lstnew_int(pid));
	if (pid == 0)
		child_first(cmd, pipefd, minishell);
	else
		parent_first(pipefd);
	if (pid == 0)
	{
		env = convert_env(minishell->env);
		if (!env && !cmd->has_path && !cmd->builtin)
			exec_failed(cmd, env, minishell, 1);
		if (cmd->builtin)
			builtin_pipe(cmd, env, minishell);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			exec_failed(cmd, env, minishell, 1);
	}
	close(minishell->m_fd[0]);
	close(minishell->m_fd[1]);
	return (0);
}
