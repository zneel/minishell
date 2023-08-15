/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:52:56 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/15 16:13:21 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_in(t_command *cmd, t_minishell *minishell)
{
	int	fdin;

	if (cmd->has_heredoc == false)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(FILE_HEREDOC, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == false)
			exit(free_and_msg("No such file or directory", cmd->file_in,
					minishell, cmd));
		else
			exit(free_and_msg("No such file or directory", FILE_HEREDOC,
					minishell, cmd));
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	dup_out(t_command *cmd, t_minishell *minishell)
{
	int	fdout;

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

void	exec_annexe_builtin(t_command *cmd, char **env, t_minishell *minishell)
{
	int	status;

	if (cmd->builtin != W_PATH)
		status = exec_builtin(cmd, minishell, true);
	else
		status = 1;
	exec_failed(cmd, env, minishell, status);
}

void	execute_command(t_command *cmd, t_minishell *minishell)
{
	pid_t	pid;
	char	**env;

	if (cmd->has_heredoc == true)
		here_doc(cmd->file_in);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		dup_in(cmd, minishell);
		dup_out(cmd, minishell);
		env = convert_env(minishell->env);
		if (!env)
			exec_failed(cmd, env, minishell, 1);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			exec_failed(cmd, env, minishell, 1);
	}
	else
		ft_lstadd_back(&minishell->pids, ft_lstnew(&pid));
}
