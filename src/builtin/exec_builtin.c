/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:14:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/24 23:16:16 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	prep_exec_builtin(t_command *cmd)
{
	int	fdin;
	int	fdout;

	if (cmd->has_heredoc == true)
		here_doc(cmd->file_in);
	if (cmd->has_append == false)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC, 0644);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND, 0644);
	if (cmd->has_heredoc == false)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(file_heredoc, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == false)
			return (msg_error("No such file or directory", cmd->file_in));
		else
			return (msg_error("No such file or directory", file_heredoc));
	}
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(fdin);
	close(fdout);
	return (0);
}

int	end_builtin(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (0);
}

int	search_builtin(t_command *cmd, t_minishell *minishell, int builtin)
{
	if (builtin == ECHO)
	{
		if (echo(cmd))
			return (1);
	}
	else if (builtin == PWD)
	{
		if (pwd(*minishell))
			return (1);
	}
	else if (builtin == EXPORT)
	{
		if (export(cmd, minishell))
			return (1);
	}
	else if (builtin == ENV)
	{
		if (print_env(*minishell))
			return (1);
	}
	else if (builtin == UNSET)
	{
		if (unset(cmd, minishell))
			return (1);
	}
	else if (builtin == CD)
	{
		
	}
	return (0);
}

int	exec_builtin(t_command *cmd, t_minishell *minishell)
{
	int stdin;
	int stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (prep_exec_builtin(cmd))
		return (1);
	if (search_builtin(cmd, minishell, check_builtin(cmd)))
		return (1);
	if (end_builtin(stdin, stdout))
		return (1);
	return (0);
}
