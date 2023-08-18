/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:52:56 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/02 11:46:10 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

void	dup_in(t_command *cmd)
{
	int	fdin;

	if (cmd->has_heredoc == false)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(FILE_HEREDOC, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == false)
			exit(msg_error("No such file or directory", cmd->file_in));
		else
			exit(msg_error("No such file or directory", FILE_HEREDOC));
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	dup_out(t_command *cmd)
{
	int	fdout;

	if (cmd->has_append == false)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND);
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
	if (g_sigint == 1)
		return ;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		dup_in(cmd);
		dup_out(cmd);
		env = convert_env(minishell->env);
		if (!env)
			exec_failed(cmd, env, minishell, 1);
		if (execve(cmd->command[0], cmd->command, env) == -1)
			exec_failed(cmd, env, minishell, 1);
	}
	else
	{
		signal(SIGINT, sig_handler_job);
		signal(SIGQUIT, sig_handler_job);
		ft_lstadd_back(&minishell->pids, ft_lstnew(&pid));
	}
}
