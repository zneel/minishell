/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:56:41 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 11:25:52 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_last(int pipefd[2][2])
{
	close_if(pipefd[0][0]);
	pipefd[0][0] = -1;
}

void	child_last(t_command *cmd, int pipefd[2][2], t_minishell *ms)
{
	if (cmd->has_good_file == false)
		close_all_pipe_free(pipefd, ms, cmd);
	if (cmd->mode & (M_HERE_DOC | M_IN))
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
	if (dup_out(cmd))
		close_all_pipe_free(pipefd, ms, cmd);
}

int	execute_last(t_command *cmd, t_minishell *minishell, int pipefd[2][2])
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid != 0)
		ft_lstadd_back(&minishell->pids, ft_lstnew_int(pid));
	if (pid == 0)
		child_last(cmd, pipefd, minishell);
	else
		parent_last(pipefd);
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
