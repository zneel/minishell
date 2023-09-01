/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:39 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 17:00:58 by ebouvier         ###   ########.fr       */
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

void	for_in(int pipefd[2][2], t_command *cmd, t_minishell *ms)
{
	if (cmd->mode & (M_IN | M_HERE_DOC))
	{
		close_if(pipefd[0][1]);
		close_if(pipefd[0][0]);
		if (dup_in(cmd))
			close_all_pipe_free(pipefd, ms, cmd);
	}
	else
	{
		close_if(pipefd[0][1]);
		dup2(pipefd[0][0], STDIN_FILENO);
		close_if(pipefd[0][0]);
	}
}

void	for_out(int pipefd[2][2], t_command *cmd, t_minishell *ms)
{
	if (cmd->mode & (M_OUT | M_APPEND))
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
}

void	child_middle(int pipefd[2][2], t_command *cmd, t_minishell *ms)
{
	if (!cmd->has_good_file)
		close_all_pipe_free(pipefd, ms, cmd);
	for_in(pipefd, cmd, ms);
	for_out(pipefd, cmd, ms);
	close_if(ms->m_fd[0]);
	close_if(ms->m_fd[1]);
}

int	execute_middle(t_command *cmd, t_minishell *minishell, int pipefd[2][2])
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid != 0)
		ft_lstadd_back(&minishell->pids, ft_lstnew_int(pid));
	if (pid == 0)
		child_middle(pipefd, cmd, minishell);
	else
		parent_middle(pipefd);
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
	return (0);
}
